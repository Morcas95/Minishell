#include "minishell.h"

static int	handle_plain_piece(const char *s, int *i, char **out)
{
	char	*piece;
	int		start;

	start = *i;
	while (s[*i] && s[*i] != '$' && s[*i] != ' ' && s[*i] != '\t'
		&& s[*i] != '\'' && s[*i] != '"' && !is_operator(s[*i]))
		(*i)++;
	piece = const_ft_substr(s, start, *i - start);
	if (!piece)
		return (-1);
	if (append_text(out, piece) < 0)
		return (free(piece), -1);
	return (free(piece), 0);
}

int	extract_plain(const char *s, int *i, char **out, t_env_ctx *ctx)
{
	*out = NULL;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\''
		&& s[*i] != '"' && !is_operator(s[*i]))
	{
		if (s[*i] == '$')
		{
			(*i)++;
			if (append_env_var(s, i, out, ctx) < 0)
				return (-1);
		}
		else if (handle_plain_piece(s, i, out) < 0)
			return (-1);
	}
	if (!*out)
		*out = ft_strdup("");
	if (!*out)
		return (-1);
	return (0);
}

static int	handle_quoted_piece(const char *s, int *i, char **out, char q)
{
	char	*piece;
	int		start;

	start = *i;
	while (s[*i] && s[*i] != q && !(q == '"' && s[*i] == '$'))
		(*i)++;
	piece = const_ft_substr(s, start, *i - start);
	if (!piece)
		return (-1);
	if (append_text(out, piece) < 0)
		return (free(piece), -1);
	return (free(piece), 0);
}

int	extract_quoted(const char *s, int *i, char **out, t_env_ctx *ctx)
{
	char	q;

	q = s[*i];
	*out = NULL;
	(*i)++;
	while (s[*i] && s[*i] != q)
	{
		if (q == '"' && s[*i] == '$')
		{
			(*i)++;
			if (append_env_var(s, i, out, ctx) < 0)
				return (-1);
		}
		else if (handle_quoted_piece(s, i, out, q) < 0)
			return (-1);
	}
	if (!s[*i])
		return (-1);
	if (!*out)
		*out = ft_strdup("");
	if (!*out)
		return (-1);
	return ((*i)++, 0);
}

char	*extract_word(char *str, int *i, t_env_ctx *ctx)
{
	char	*part;
	char	*result;

	result = NULL;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !is_operator(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (extract_quoted(str, i, &part, ctx) < 0)
				return (free(result), NULL);
		}
		else
		{
			if (extract_plain(str, i, &part, ctx) < 0)
				return (free(result), NULL);
		}
		result = ft_strjoin(result, part);
		free(part);
		if (!result)
			return (NULL);
	}
	return (result);
}
