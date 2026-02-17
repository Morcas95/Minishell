#include "minishell.h"

int	resolve_direct_path(const char *cmd, char **out_path)
{
	if (!out_path || !cmd)
		return (-1);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			*out_path = ft_strdup(cmd);
			if (!*out_path)
				return (-1);
			return (0);
		}
		else
			return (-1);
	}
	return (1);
}

int	resolve_via_path(const char *cmd, char **envp, char **out_path)
{
	const char	*path_val;
	size_t		tokens;
	char		**dirs;
	int			r;

	if (!cmd || !out_path)
		return (-1);
	path_val = get_env_value(envp, "PATH");
	if (!path_val || *path_val == '\0')
		return (-1);
	tokens = count_dots(path_val, ':');
	dirs = ft_split_pipex(path_val, ':');
	if (!dirs)
		return (-1);
	r = scan_dirs_tokens(dirs, tokens, cmd, out_path);
	free_all(dirs);
	if (r == 1)
		return (0);
	return (-1);
}

const char	*get_env_value(char **envp, const char *key)
{
	int	key_len;
	int	i;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}