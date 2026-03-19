/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:33:57 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/19 12:33:29 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (0);
}

void	print_cmd_error(const char *cmd, const char *msg)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(msg);
}
