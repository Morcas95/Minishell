/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_welcome.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:27:08 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/11 16:03:44 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_welcome(void)
{
	int		fd;
	char	*line;

	fd = open("src/shell_welcome/welcome_txt.txt", O_RDONLY);
	ft_putstr("\x1B"
				"c");
	ft_putstr_fd("\033[38;5;208m", STDOUT_FILENO);
	if (fd < 0)
		return ;
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			if (ft_strncmp(line, "━━━━━━━━", 18) == 0)
				ft_putstr_fd("\033[38;5;39m", STDOUT_FILENO);
			ft_putstr_fd(line, STDOUT_FILENO);
			if (ft_strncmp(line, "━━━━━━━━", 18) == 0)
				ft_putstr_fd("\033[38;5;208m", STDOUT_FILENO);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
}
