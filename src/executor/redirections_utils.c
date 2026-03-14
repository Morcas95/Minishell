#include "minishell.h"

void	write_expanded(int fd, char *expanded)
{
	if (!expanded)
		return ;
	write(fd, expanded, strlen(expanded));
	free(expanded);
}

char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = const_ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

char	*append_str(char *result, char *value)
{
	char	*tmp;

	tmp = const_ft_strjoin(result, value);
	free(result);
	free(value);
	return (tmp);
}

char	*resolve_var(const char *line, int *i, char **envp, int last_exit_status)
{
	char	*name;
	char	*value;
	int		start;

	if (line[*i] == '?')
		return ((*i)++, ft_itoa(last_exit_status));
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return (NULL);
	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	name = const_ft_substr(line, start, *i - start);
	if (!name)
		return (NULL);
	value = (char *)get_env_value(envp, name);
	free(name);
	if(value)
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	return (value);
}