/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:28:47 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 19:20:52 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor_temp(t_cmd *temp, char ***envp)
{
	t_redir	*redir;
	char	*tmp_file;

	while (temp)
	{
		redir = temp->redirects;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				tmp_file = read_heredoc(redir->file, 1, *envp, 0);
				redir->type = REDIR_IN;
				free(redir->file);
				redir->file = tmp_file;
			}
			redir = redir->next;
		}
		temp = temp->next;
	}
	return (0);
}

int	executor_cmd_pid_0(int prev_fd, t_cmd *cmd, int *pipe_fd, char ***envp)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	if (apply_redirections(cmd->redirects, 1, *envp, 0) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, envp));
	execute_external(cmd, *envp);
	return (0);
}

int	executor_cmd(t_cmd *cmd, int num_cmds, int *pipe_fd, char ***envp)
{
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipe_fd) < 0)
				return (perror("minishell: pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			executor_cmd_pid_0(prev_fd, cmd, pipe_fd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		num_cmds++;
		cmd = cmd->next;
	}
	return (0);
}
