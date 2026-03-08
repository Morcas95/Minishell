#include "minishell.h"

static int	is_same_cmd(const char *left, const char *right)
{
	size_t	len;

	if (!left || !right)
		return (0);
	len = ft_strlen(right) + 1;
	return (ft_strncmp((char *)left, right, len) == 0);
}

int	is_builtin(const char *cmd)
{
	return (is_same_cmd(cmd, "echo") || is_same_cmd(cmd, "cd")
		|| is_same_cmd(cmd, "pwd") || is_same_cmd(cmd, "export")
		|| is_same_cmd(cmd, "unset") || is_same_cmd(cmd, "env")
		|| is_same_cmd(cmd, "exit"));
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_same_cmd(cmd->args[0], "echo"))
		return (builtin_echo(cmd->args));
	if (is_same_cmd(cmd->args[0], "cd"))
		return (builtin_cd(cmd->args, envp));
	if (is_same_cmd(cmd->args[0], "pwd"))
		return (builtin_pwd());
	if (is_same_cmd(cmd->args[0], "export"))
		return (builtin_export(cmd->args, envp));
	if (is_same_cmd(cmd->args[0], "unset"))
		return (builtin_unset(cmd->args, envp));
	if (is_same_cmd(cmd->args[0], "env"))
		return (builtin_env(*envp));
	if (is_same_cmd(cmd->args[0], "exit"))
		return (builtin_exit(cmd->args));
	return (1);
}
