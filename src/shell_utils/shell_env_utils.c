/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:53:55 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/19 11:13:34 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

void	free_envp_copy(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**dup_envp(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = env_count(envp);
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
