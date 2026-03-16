/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:11:51 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/16 17:12:08 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	char	**shell_env;
	int		last_exit_status;

	(void)argc;
	(void)argv;
	shell_env = dup_envp(envp);
	if (!shell_env)
		return (perror("minishell: malloc"), 1);
	last_exit_status = 0;
	setup_signals();
	//shell_welcome();
	shell_execution(shell_env, last_exit_status);
	free_envp_copy(shell_env);
	return (0);
}
