/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:21:32 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 19:21:33 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(const char *line, char **envp,
		int last_exit_status)
{
	char	*result;
	char	*value;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (result && line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			value = resolve_var(line, &i, envp, last_exit_status);
			if (!value)
				result = append_char(result, '$');
			else
				result = append_str(result, value);
		}
		else
			result = append_char(result, line[i++]);
	}
	return (result);
}

char	*read_heredoc(char *delimiter, int has_cmd, char **envp,
		int last_exit_status)
{
	int		fd;
	char	*prompt;
	char	*filename;

	if (has_cmd == 1)
	{
		filename = ft_strdup("/tmp/.heredoc_minishell");
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (free(filename), NULL);
	}
	while (1)
	{
		prompt = readline("> ");
		if (!prompt || ft_strcmp(prompt, delimiter) == 0)
			return (free(prompt), close(fd), filename);
		write_expanded(fd, expand_heredoc_line(prompt, envp, last_exit_status));
		free(prompt);
		write(fd, "\n", 1);
	}
}

/*
 * Apply all redirections from command
 * Called in child process before execve
 * Returns: 0 on success, -1 on error
 */
int	apply_redirections(t_redir *redirects, int has_cmd, char **envp,
		int last_exit_status)
{
	char	*tmp_file;

	while (redirects)
	{
		if (redirects->type == REDIR_IN)
			redd_in(redirects);
		else if (redirects->type == REDIR_OUT)
			redd_out(redirects);
		else if (redirects->type == REDIR_APPEND)
			redd_append(redirects);
		else if (redirects->type == REDIR_HEREDOC)
		{
			tmp_file = read_heredoc(redirects->file, has_cmd, envp,
					last_exit_status);
			if (has_cmd == 1)
				redd_heredoc(tmp_file);
		}
		redirects = redirects->next;
	}
	return (0);
}
