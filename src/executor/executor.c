/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:26:22 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 19:21:07 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_external(t_cmd *cmd, char **envp)
{
	char	*path;
	int		ret;

	path = NULL;
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (has_slash(cmd->args[0]))
		ret = resolve_direct_path(cmd->args[0], &path);
	else
		ret = resolve_via_path(cmd->args[0], envp, &path);
	if (ret == -2)
	{
		print_error("minishell: ");
		print_error(cmd->args[0]);
		print_error(": Permission denied\n");
		exit(126);
	}
	if (!path)
	{
		print_error("minishell: ");
		print_error(cmd->args[0]);
		print_error(": command not found\n");
		exit(127);
	}
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

/*
 * Main execution function
 * Returns: exit status of last command
 */
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
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_cmd *cmd, char ***envp)
{
	int		pipe_fd[2];
	int		num_cmds;
	int		status;
	int		last_status;
	t_cmd	*temp;

	num_cmds = 0;
	last_status = 0;
	temp = cmd;
	executor_temp(temp, envp);
	executor_cmd(cmd, num_cmds, pipe_fd, envp);
	while (num_cmds)
	{
		wait(&status);
		if (num_cmds == 1 && WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		num_cmds--;
	}
	return (last_status);
}
