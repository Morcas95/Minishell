#include "minishell.h"

int			g_signal = 0;
int			g_last_exit_status = 0;

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
void	process_input(char *input, char ***envp)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		exit_status;

	if (!input || !*input)
		return ;
	tokens = lexer(input, *envp);
	if (!tokens)
		return ;
	cmds = parser(tokens);
	if (!cmds)
		return ;
	exit_status = execute(cmds, envp);
	g_last_exit_status = exit_status;
	printf("Exit status: %d\n", exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char *prompt;
	char **shell_env;

	(void)argc;
	(void)argv;
	shell_env = dup_envp(envp);
	if (!shell_env)
		return (perror("minishell: malloc"), 1);

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
		process_input(prompt, &shell_env);
		free(prompt);
	}
	free_envp_copy(shell_env);
	return (0);
}