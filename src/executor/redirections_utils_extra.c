/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_extra.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:10:12 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 19:20:40 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redd_in(t_redir *redirects)
{
	int	fd;

	fd = open(redirects->file, O_RDONLY);
	if (fd == -1)
		return (perror("minishell: input"), -1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	redd_out(t_redir *redirects)
{
	int	fd;

	fd = open(redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("minishell: output"), -1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redd_append(t_redir *redirects)
{
	int	fd;

	fd = open(redirects->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("minishell: append"), -1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redd_heredoc(char *tmp_file)
{
	int	fd;

	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_RDONLY);
	if (fd == -1)
	{
		free(tmp_file);
		return (perror("minishell: heredoc"), -1);
	}
	dup2(fd, 0);
	close(fd);
	unlink(tmp_file);
	free(tmp_file);
	return (0);
}
