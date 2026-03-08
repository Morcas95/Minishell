#include "minishell.h"

static int	find_env_index(char **envp, const char *name)
{
	size_t	name_len;
	int		index;

	name_len = ft_strlen(name);
	index = 0;
	while (envp && envp[index])
	{
		if (ft_strncmp(envp[index], name, name_len) == 0
			&& envp[index][name_len] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static int	set_env_pair(char ***envp, const char *name, const char *value)
{
	char	*prefix;
	char	*pair;
	int		index;

	prefix = const_ft_strjoin(name, "=");
	if (!prefix)
		return (1);
	pair = const_ft_strjoin(prefix, value);
	free(prefix);
	if (!pair)
		return (1);
	index = find_env_index(*envp, name);
	if (index >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = pair;
		return (0);
	}
	free(pair);
	return (1);
}

int	builtin_cd(char **args, char ***envp)
{
	char		*old_pwd;
	char		*target;
	char		*new_pwd;
	const char	*home;

	if (args[1] && args[2])
		return (ft_putendl_fd("minishell: cd: too many arguments",
				STDERR_FILENO), 1);
	if (args[1])
		target = args[1];
	else
	{
		home = get_env_value(*envp, "HOME");
		if (!home)
			return (ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO),
				1);
		target = (char *)home;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		set_env_pair(envp, "OLDPWD", old_pwd);
	if (new_pwd)
		set_env_pair(envp, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
