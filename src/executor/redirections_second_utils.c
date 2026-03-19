/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_second_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:44:29 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 12:54:51 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_one_redir(t_redir *r, int has_cmd, char **envp, int last_exit_status)
{
	if (r->type == REDIR_IN)
		return (apply_redir_in(r->file));
	if (r->type == REDIR_OUT)
		return (apply_redir_out(r->file, O_WRONLY | O_CREAT | O_TRUNC));
	if (r->type == REDIR_APPEND)
		return (apply_redir_out(r->file, O_WRONLY | O_CREAT | O_APPEND));
	if (r->type == REDIR_HEREDOC)
		return (apply_heredoc(r, has_cmd, envp, last_exit_status));
	return (0);
}

int	apply_redir_in(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("minishell: input"), -1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	apply_redir_out(const char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		return (perror("minishell: output"), -1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	apply_heredoc(t_redir *r, int has_cmd, char **envp,
		int last_exit_status)
{
	char	*tmp_file;
	int		fd;

	tmp_file = read_heredoc(r->file, has_cmd, envp, last_exit_status);
	if (has_cmd != 1)
		return (0);
	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
		return (free(tmp_file), perror("minishell: heredoc"), -1);
	dup2(fd, 0);
	close(fd);
	unlink(tmp_file);
	free(tmp_file);
	return (0);
}
