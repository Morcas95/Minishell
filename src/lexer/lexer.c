#include "minishell.h"

int	append_text(char **result, const char *text)
{
	char	*joined;

	if (!text)
		return (0);
	joined = ft_strjoin(*result, (char *)text);
	if (!joined)
		return (-1);
	*result = joined;
	return (0);
}

int	append_exit_status(char **result, int last_exit_status)
{
	char	*status;
	int		r;

	status = ft_itoa(last_exit_status);
	if (!status)
		return (-1);
	r = append_text(result, status);
	free(status);
	return (r);
}

int	append_env_var(const char *s, int *i, char **result, t_env_ctx *ctx)
{
	int		start;
	char	*name;
	char	*value;

	if (s[*i] == '?')
		return ((*i)++, append_exit_status(result, ctx->last_exit_status));
	if (ft_isdigit(s[*i]))
		return ((*i)++, 0);
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
		return (append_text(result, "$"));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = const_ft_substr(s, start, *i - start);
	if (!name)
		return (-1);
	value = (char *)get_env_value(ctx->envp, name);
	free(name);
	if (value)
		return (append_text(result, value));
	return (0);
}

static int	append_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
		(*current)->next = new_token;
	*current = new_token;
	return (1);
}

t_token	*lexer(char *input, t_env_ctx *ctx)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;

	if (!input || !*input)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		new_token = extract_token(input, &i, ctx);
		if (!new_token)
			return (free_tokens(head), NULL);
		append_token(&head, &current, new_token);
	}
	return (head);
}
