/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:19:05 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/19 11:12:27 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: pwd"), 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}

int	builtin_env(char **envp)
{
	int	index;

	index = 0;
	while (envp && envp[index])
	{
		if (ft_strchr(envp[index], '='))
			ft_putendl_fd(envp[index], STDOUT_FILENO);
		index++;
	}
	return (0);
}
