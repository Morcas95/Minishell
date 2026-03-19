/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:11:57 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 13:20:15 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_args(t_token *tokens)
{
	int		count;
	char	**args;
	t_token	*prev;

	prev = NULL;
	count = count_words_until_pipe(tokens);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			if (!prev || prev->type == TOKEN_WORD || prev->type == TOKEN_PIPE)
				args[count++] = strdup(tokens->value);
		prev = tokens;
		tokens = tokens->next;
	}
	args[count] = NULL;
	return (args);
}

int	count_words_until_pipe(t_token *tokens)
{
	int		count;
	t_token	*prev;

	count = 0;
	prev = NULL;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (!prev || prev->type == TOKEN_WORD || prev->type == TOKEN_PIPE)
				count++;
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (count);
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}
