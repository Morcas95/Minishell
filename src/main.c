#include "minishell.h"

int			g_signal = 0;

static int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static char	**dup_envp(char **envp)
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

static void	free_envp_copy(char **envp)
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

/*
 * Process the input line
 * Tokenizes and prints tokens for debugging
 */
int	process_input(char *input, char ***envp, int last_exit_status)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		exit_status;

	if (!input || !*input)
		return (last_exit_status);
	tokens = lexer(input, *envp, last_exit_status);
	if (!tokens)
		return (last_exit_status);
	cmds = parser(tokens);
	if (!cmds)
		return (last_exit_status);
	exit_status = execute(cmds, envp);
	printf("Exit status: %d\n", exit_status);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char *prompt;
	char **shell_env;
	int last_exit_status;

	(void)argc;
	(void)argv;
	shell_env = dup_envp(envp);
	if (!shell_env)
		return (perror("minishell: malloc"), 1);
	last_exit_status = 0;

	setup_signals();

	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
		{
			break ;
		}
		if (*prompt)
			add_history(prompt);
		last_exit_status = process_input(prompt, &shell_env, last_exit_status);
		free(prompt);
	}
	free_envp_copy(shell_env);
	return (0);
}