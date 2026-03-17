#include "minishell.h"

int	has_slash(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*build_candidate(char *dir, const char *cmd)
{
	int		lb;
	int		lc;
	char	*base;
	char	*res;

	if (dir[0] == '\0')
		base = ".";
	else
		base = dir;
	lb = ft_strlen(base);
	lc = ft_strlen(cmd);
	res = (char *)malloc(lb + 1 + lc + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, base, lb);
	res[lb] = '/';
	ft_memcpy(res + lb + 1, cmd, lc);
	res[lb + 1 + lc] = '\0';
	return (res);
}

int	build_and_check(char *dir, const char *cmd, char **out_path)
{
	char	*cand;

	if (dir)
		cand = build_candidate(dir, cmd);
	else
		cand = build_candidate(".", cmd);
	if (!cand)
		return (-1);
	if (access(cand, X_OK) == 0)
	{
		*out_path = cand;
		return (1);
	}
	free(cand);
	return (0);
}

int	scan_dirs_tokens(char **dirs, size_t tokens, const char *cmd,
		char **out_path)
{
	size_t	i;
	int		r;

	i = 0;
	while (i < tokens)
	{
		r = build_and_check(dirs[i], cmd, out_path);
		if (r == 1)
			return (1);
		if (r < 0)
			return (-1);
		i++;
	}
	return (0);
}