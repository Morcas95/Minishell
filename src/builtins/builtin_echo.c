/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:18:56 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/19 11:12:31 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_n(const char *arg)
{
	size_t	index;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	index = 1;
	while (arg[index] == 'n')
		index++;
	return (arg[index] == '\0');
}

int	builtin_echo(char **args)
{
	int	arg_index;
	int	no_newline;

	arg_index = 1;
	no_newline = 0;
	while (args[arg_index] && is_flag_n(args[arg_index]))
	{
		no_newline = 1;
		arg_index++;
	}
	while (args[arg_index])
	{
		ft_putstr_fd(args[arg_index], STDOUT_FILENO);
		if (args[arg_index + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg_index++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
