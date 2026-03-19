/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:24:32 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 12:54:45 by maalonso         ###   ########.fr       */
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

int	apply_redirections(t_redir *redirects, int has_cmd, char **envp,
		int last_exit_status)
{
	while (redirects)
	{
		if (apply_one_redir(redirects, has_cmd, envp, last_exit_status) < 0)
			return (-1);
		redirects = redirects->next;
	}
	return (0);
}
