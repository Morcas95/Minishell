#include "minishell.h"

int	extract_plain(const char *s, int *i, char **out)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\''
		&& s[*i] != '"' && !is_operator(s[*i]))
		(*i)++;
	*out = const_ft_substr(s, start, *i - start);
	if (*out == NULL)
		return (-1);
	return (0);
}

int	extract_quoted(const char *s, int *i, char **out)
{
	char	q;
	int		start;

	q = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (!s[*i])
		return (-1);
	*out = const_ft_substr(s, start, *i - start);
	if (*out == NULL)
		return (-1);
	(*i)++;
	return (0);
}

/*
 * Extrae una palabra (TOKEN_WORD) del string.
 * Gestiona las comillas.
 * Retorna: el string extraído, o NULL en caso de error.
 * 
 * Extract a word (TOKEN_WORD) from string.
 * Handles quotes.
 * Returns: the extracted string, or NULL on error.
 */
char *extract_word(char *str, int *i)
{
    char *part;
	char *result;
	char *temp;

	result = NULL;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && !is_operator(str[*i]))
    {
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (extract_quoted(str, i, &part) < 0)
				return (free(result), NULL);
		}
		else
		{
			if (extract_plain(str, i, &part) < 0)
				return (free(result), NULL);
		}
		temp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = temp;
	}
    return (result);
}
