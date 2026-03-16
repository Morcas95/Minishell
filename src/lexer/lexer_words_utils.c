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

static int	append_exit_status(char **result, int last_exit_status)
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