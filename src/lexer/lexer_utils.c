/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:11:36 by maalonso          #+#    #+#             */
/*   Updated: 2026/03/19 13:04:13 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	extract_redir(char *str, int *i, t_token *token)
{
	char	op;

	op = str[*i];
	if (str[*i + 1] == op && op == '<')
		token->type = TOKEN_HEREDOC;
	else if (str[*i + 1] == op && op == '>')
		token->type = TOKEN_REDIR_APPEND;
	else if (op == '<')
		token->type = TOKEN_REDIR_IN;
	else
		token->type = TOKEN_REDIR_OUT;
	if (str[*i + 1] == op)
		(*i) += 2;
	else
		(*i)++;
}

t_token	*extract_token(char *str, int *index, t_env_ctx *ctx)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->value = NULL;
	if (str[*index] == '|')
	{
		token->type = TOKEN_PIPE;
		(*index)++;
	}
	else if (str[*index] == '<' || str[*index] == '>')
		extract_redir(str, index, token);
	else
	{
		token->type = TOKEN_WORD;
		token->value = extract_word(str, index, ctx);
		if (!token->value)
			return (free(token), NULL);
	}
	return (token);
}
