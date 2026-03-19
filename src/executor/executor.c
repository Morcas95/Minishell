/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:27:34 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 13:21:02 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_external(t_cmd *cmd, char **envp)
{
	char	*path;
	int		ret;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	path = NULL;
	if (has_slash(cmd->args[0]))
		ret = resolve_direct_path(cmd->args[0], &path);
	else
		ret = resolve_via_path(cmd->args[0], envp, &path);
	if (ret == -2)
		return (print_cmd_error(cmd->args[0], ": Permission denied\n"),
			exit(126), 0);
	if (!path)
		return (print_cmd_error(cmd->args[0], ": command not found\n"),
			exit(127), 0);
	execve(path, cmd->args, envp);
	perror("minishell: execve failed");
	exit(126);
}

static int	execute_builtin_parent(t_cmd *cmd, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (perror("minishell: dup"), 1);
	if (apply_redirections(cmd->redirects, 1, *envp, 0) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	status = exec_builtin(cmd, envp);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

int	execute(t_cmd *cmd, char ***envp)
{
	if (!cmd)
		return (0);
	if (!cmd->next && cmd->args && is_builtin(cmd->args[0]))
		return (execute_builtin_parent(cmd, envp));
	if (cmd->next)
		return (execute_pipeline(cmd, envp));
	else
		return (execute_simple(cmd, envp));
}

int	execute_simple(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	int		status;
	int		redirect;

	redirect = 1;
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->redirects)
			redirect = 0;
		else
			return (0);
	}
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
	{
		if (apply_redirections(cmd->redirects, redirect, *envp, 0) < 0)
			exit(1);
		if (is_builtin(cmd->args[0]))
			exit(exec_builtin(cmd, envp));
		execute_external(cmd, *envp);
	}
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int	execute_pipeline(t_cmd *cmd, char ***envp)
{
	int	pipe_fd[2];
	int	prev_fd;
	int	num_cmds;

	prev_fd = -1;
	num_cmds = 0;
	resolve_heredocs(cmd, *envp);
	while (cmd)
	{
		if (fork_and_pipe(cmd, pipe_fd, &prev_fd, envp) < 0)
			return (1);
		num_cmds++;
		cmd = cmd->next;
	}
	return (wait_all(num_cmds));
}
