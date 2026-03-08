#include "minishell.h"

static int	append_text(char **result, const char *text)
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

static int	append_exit_status(char **result)
{
	char	*status;
	int		r;

	status = ft_itoa(g_last_exit_status);
	if (!status)
		return (-1);
	r = append_text(result, status);
	free(status);
	return (r);
}

static int	append_env_var(const char *s, int *i, char **result, char **envp)
{
	int		start;
	char	*name;
	char	*value;

	if (s[*i] == '?')
	{
		(*i)++;
		return (append_exit_status(result));
	}
	if (ft_isdigit(s[*i]))
	{
		(*i)++;
		return (0);
	}
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
		return (append_text(result, "$"));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = const_ft_substr(s, start, *i - start);
	if (!name)
		return (-1);
	value = (char *)get_env_value(envp, name);
	free(name);
	if (value)
		return (append_text(result, value));
	return (0);
}

int	extract_plain(const char *s, int *i, char **out, char **envp)
{
	int		start;
	char	*piece;

	*out = NULL;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\''
		&& s[*i] != '"' && !is_operator(s[*i]))
	{
		if (s[*i] == '$')
		{
			(*i)++;
			if (append_env_var(s, i, out, envp) < 0)
				return (-1);
		}
		else
		{
			start = *i;
			while (s[*i] && s[*i] != '$' && s[*i] != ' ' && s[*i] != '\t'
				&& s[*i] != '\'' && s[*i] != '"' && !is_operator(s[*i]))
				(*i)++;
			piece = const_ft_substr(s, start, *i - start);
			if (!piece)
				return (-1);
			if (append_text(out, piece) < 0)
				return (free(piece), -1);
			free(piece);
		}
	}
	if (!*out)
		*out = ft_strdup("");
	if (!*out)
		return (-1);
	return (0);
}
/*
 * Extrae las palabras entrecomilladas de un string
 * Modifica
 * Retorna: 0 si hubo éxito, -1 si hubo algun error.
 *
 * Extract the quoted words of a string
 * Returns: 0 if success, -1 if error.
 */
int	extract_quoted(const char *s, int *i, char **out, char **envp)
{
	char	q;
	int		start;
	char	*piece;

	q = s[*i];
	*out = NULL;
	(*i)++;
	while (s[*i] && s[*i] != q)
	{
		if (q == '"' && s[*i] == '$')
		{
			(*i)++;
			if (append_env_var(s, i, out, envp) < 0)
				return (-1);
		}
		else
		{
			start = *i;
			while (s[*i] && s[*i] != q && !(q == '"' && s[*i] == '$'))
				(*i)++;
			piece = const_ft_substr(s, start, *i - start);
			if (!piece)
				return (-1);
			if (append_text(out, piece) < 0)
				return (free(piece), -1);
			free(piece);
		}
	}
	if (!s[*i])
		return (-1);
	if (!*out)
		*out = ft_strdup("");
	if (!*out)
		return (-1);
	(*i)++;
	return (0);
}

/*
 * Extrae una palabra (TOKEN_WORD) del string.
 * Retorna: el string extraído, o NULL en caso de error.
 *
 * Extract a word (TOKEN_WORD) from string.
 * Returns: the extracted string, or NULL on error.
 */
char	*extract_word(char *str, int *i, char **envp)
{
	char	*part;
	char	*result;

	result = NULL;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !is_operator(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (extract_quoted(str, i, &part, envp) < 0)
				return (free(result), NULL);
		}
		else
		{
			if (extract_plain(str, i, &part, envp) < 0)
				return (free(result), NULL);
		}
		result = ft_strjoin(result, part);
		free(part);
		if (!result)
			return (NULL);
	}
	return (result);
}
