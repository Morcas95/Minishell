#include "minishell.h"

static int	env_size(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static int	is_valid_identifier(const char *name)
{
	size_t	index;

	if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	index = 1;
	while (name[index])
	{
		if (!ft_isalnum(name[index]) && name[index] != '_')
			return (0);
		index++;
	}
	return (1);
}

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

static void	remove_env_index(char **envp, int remove_index)
{
	int	index;
	int	count;

	count = env_size(envp);
	free(envp[remove_index]);
	index = remove_index;
	while (index < count)
	{
		envp[index] = envp[index + 1];
		index++;
	}
}

int	builtin_unset(char **args, char ***envp)
{
	int	index;
	int	found_index;

	index = 1;
	while (args[index])
	{
		if (is_valid_identifier(args[index]))
		{
			found_index = find_env_index(*envp, args[index]);
			if (found_index >= 0)
				remove_env_index(*envp, found_index);
		}
		index++;
	}
	return (0);
}
