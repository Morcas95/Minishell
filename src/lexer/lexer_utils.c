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
	if (str[*i + 1] == op)
	{
		token->type = (op == '<') ? TOKEN_HEREDOC : TOKEN_REDIR_APPEND;
		(*i) += 2;
	}
	else
	{
		token->type = (op == '<') ? TOKEN_REDIR_IN : TOKEN_REDIR_OUT;
		(*i)++;
	}
}

t_token	*extract_token(char *str, int *i, t_env_ctx *ctx)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->value = NULL;
	if (str[*i] == '|')
	{
		token->type = TOKEN_PIPE;
		(*i)++;
	}
	else if (str[*i] == '<' || str[*i] == '>')
		extract_redir(str, i, token);
	else
	{
		token->type = TOKEN_WORD;
		token->value = extract_word(str, i, ctx);
		if (!token->value)
			return (free(token), NULL);
	}
	return (token);
}