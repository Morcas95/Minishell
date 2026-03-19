/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:24:19 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 12:35:27 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(int num_cmds)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (num_cmds)
	{
		wait(&status);
		if (num_cmds == 1 && WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		num_cmds--;
	}
	return (last_status);
}

void	child_pipeline(t_cmd *cmd, int prev_fd, int *pipe_fd, char ***envp)
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
}

void	resolve_heredocs(t_cmd *cmd, char **envp)
{
	t_redir	*redir;
	char	*tmp_file;

	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				tmp_file = read_heredoc(redir->file, 1, envp, 0);
				free(redir->file);
				redir->file = tmp_file;
				redir->type = REDIR_IN;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	fork_and_pipe(t_cmd *cmd, int *pipe_fd, int *prev_fd, char ***envp)
{
	pid_t	pid;

	if (cmd->next && pipe(pipe_fd) < 0)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
		child_pipeline(cmd, *prev_fd, pipe_fd, envp);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	return (0);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
