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

    path = NULL;
    pid = fork();
    if (pid < 0)
        return (perror("pipex: fork"), 1);
    if (pid == 0)
    {
        if (apply_redirections(cmd->redirects) < 0)
            exit(1);
        if (has_slash(cmd->args[0]))
            resolve_direct_path(cmd->args[0], &path);
        else
            resolve_via_path(cmd->args[0], envp, &path);
        if (!path)
        {
            printf("minishell: %s: command not found\n", cmd->args[0]);
            return (127);
        }
        execve(path, cmd->args, envp);
        perror("execve failed");
        free(path);
        exit(1);
    }
    free(path);
    return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int execute_pipeline(t_cmd *cmd, char **envp)
{
    int pipe_fd[2];
    int prev_fd;
    int num_cmds;
    int status;
    int last_status;
    char *path;
    pid_t pid;

    prev_fd = -1;
    num_cmds = 0;
    last_status = 0;
    path = NULL;
    while (cmd)
    {
        if (cmd->next)
            pipe(pipe_fd);
        pid = fork();
        if (pid < 0)
            return (perror("minishell: fork"), 1);
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, 0);
                close(prev_fd);
            }
            if (cmd->next)
            {
                dup2(pipe_fd[1], 1);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
            }
            if (apply_redirections(cmd->redirects) < 0)
                exit(1);
            if (has_slash(cmd->args[0]))
                resolve_direct_path(cmd->args[0], &path);
            else
                resolve_via_path(cmd->args[0], envp, &path);
            if (!path)
            {
                printf("minishell: %s: command not found\n", cmd->args[0]);
                exit(127);
            }
            execve(path, cmd->args, envp);
            perror("minishell: execve failed");
            free(path);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        num_cmds++;
        cmd = cmd->next;
    }
    while (num_cmds)
    {
        wait(&status);
        if (num_cmds == 1)
            last_status = WEXITSTATUS(status);
        num_cmds--;
    }
    return (last_status);
}