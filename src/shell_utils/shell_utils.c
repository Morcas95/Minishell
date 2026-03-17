/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:27:08 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/03/17 02:48:14 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(void)
{
	char	*cwd;
	char	*prefix;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("?");
	if (!cwd)
		return (NULL);
	prefix = const_ft_strjoin("\001\033[32m\002minishell\001\033[90m\002@"
			"\001\033[38;5;31m\002", cwd);
	free(cwd);
	if (!prefix)
		return (NULL);
	tmp = const_ft_strjoin(prefix, "> \001\033[0m\002");
	free(prefix);
	if (!tmp)
		return (NULL);
	prompt = tmp;
	return (prompt);
}

int	shell_execution(char **shell_env, int last_exit_status)
{
	char	*prompt_text;
	char	*prompt;

	while (1)
	{
		prompt_text = build_prompt();
		if (!prompt_text)
			return (free_envp_copy(shell_env), perror("minishell: malloc"), 1);
		prompt = readline(prompt_text);
		free(prompt_text);
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		last_exit_status = process_input(prompt, &shell_env, last_exit_status);
		free(prompt);
	}
	return (0);
}

void	shell_welcome(void)
{
	int		fd;
	char	*line;

	fd = open("src/shell_utils/welcome_txt.txt", O_RDONLY);
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

/*
 * Process the input line
 * Tokenizes and prints tokens for debugging
 */
int	process_input(char *input, char ***envp, int last_exit_status)
{
	t_token	*tokens;
	t_cmd	*cmds;
	t_env_ctx ctx;
	int		exit_status;

	if (!input || !*input)
		return (last_exit_status);
	ctx.envp = *envp;
	ctx.last_exit_status = last_exit_status;
	tokens = lexer(input, &ctx);
	if (!tokens)
		return (last_exit_status);
	cmds = parser(tokens);
	if (!cmds)
		return (last_exit_status);
	exit_status = execute(cmds, envp);
	free_cmd_list(cmds);
	return (exit_status);
}
