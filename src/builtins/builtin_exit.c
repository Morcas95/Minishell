/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:19:00 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 17:19:43 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	size_t	index;

	if (!str || !str[0])
		return (0);
	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	if (!str[index])
		return (0);
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	long long	value;

	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO), 1);
	errno = 0;
	value = ft_atoi(args[1]);
	if (errno == ERANGE)
		exit(2);
	exit((unsigned char)value);
}
