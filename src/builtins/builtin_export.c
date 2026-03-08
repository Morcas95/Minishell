#include "minishell.h"

static int	env_size(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static int	find_env_index(char **envp, const char *name, size_t name_len)
{
	int	index;

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

static int	is_valid_identifier(const char *name)
{
	size_t	index;

	if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	index = 1;
	while (name[index] && name[index] != '=')
	{
		if (!ft_isalnum(name[index]) && name[index] != '_')
			return (0);
		index++;
	}
	return (1);
}

static int	set_or_add_env(char ***envp, char *arg)
{
	char	**new_env;
	size_t	name_len;
	int		index;
	int		count;

	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	if (arg[name_len] != '=')
		return (0);
	index = find_env_index(*envp, arg, name_len);
	if (index >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = ft_strdup(arg);
		return ((*envp)[index] == NULL);
	}
	count = env_size(*envp);
	new_env = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	ft_memcpy(new_env, *envp, sizeof(char *) * count);
	new_env[count] = ft_strdup(arg);
	new_env[count + 1] = NULL;
	if (!new_env[count])
		return (free(new_env), 1);
	free(*envp);
	*envp = new_env;
	return (0);
}

int	builtin_export(char **args, char ***envp)
{
	int	index;
	int	has_error;

	if (!args[1])
		return (builtin_env(*envp));
	index = 1;
	has_error = 0;
	while (args[index])
	{
		if (!is_valid_identifier(args[index]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[index], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			has_error = 1;
		}
		else if (set_or_add_env(envp, args[index]) != 0)
			return (1);
		index++;
	}
	return (has_error);
}
