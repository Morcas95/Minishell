#include "minishell.h"

/*
 * Main execution function
 * Returns: exit status of last command
 */
int execute(t_cmd *cmd, char **envp)
{
    if (!cmd)
        return (0);
    if (cmd->next)
        return (execute_pipeline(cmd, envp));
    else
    return (execute_simple(cmd, envp));
}

int execute_simple(t_cmd *cmd, char **envp)
{
    char *path;
    pid_t pid;
    int status;

    if (has_slash(cmd->args[0]))
        resolve_direct_path(cmd->args[0], &path);
    else
        resolve_via_path(cmd->args[0], envp, &path);
    if (!path)
    {
        printf("minishell: %s: command not found\n", cmd->args[0]);
        return (127);
    }
    pid = fork();
    if (pid < 0)
        return (perror("pipex: fork"), 1);
    if (pid == 0)
    {
        execve(path, cmd->args, envp);
        perror("execve failed");
        free(path);
        exit(1);
    }
    free(path);
    return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}