#include "minishell.h"

static int	execute_external(t_cmd *cmd, char **envp)
{
    char	*path;

    path = NULL;
    if (!cmd->args || !cmd->args[0])
        exit(0);
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

static int	execute_builtin_parent(t_cmd *cmd, char ***envp)
{
    int	saved_stdin;
    int	saved_stdout;
    int	status;

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdin < 0 || saved_stdout < 0)
        return (perror("minishell: dup"), 1);
    if (apply_redirections(cmd->redirects, 1, *envp, 0) < 0)
    {
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return (1);
    }
    status = exec_builtin(cmd, envp);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    return (status);
}

/*
 * Main execution function
 * Returns: exit status of last command
 */
int execute(t_cmd *cmd, char ***envp)
{
    if (!cmd)
        return (0);
    if (!cmd->next && cmd->args && is_builtin(cmd->args[0]))
        return (execute_builtin_parent(cmd, envp));
    if (cmd->next)
        return (execute_pipeline(cmd, envp));
    else
        return (execute_simple(cmd, envp));
}

int execute_simple(t_cmd *cmd, char ***envp)
{
    pid_t pid;
    int status;
    int redirect;

    redirect = 1;
    if (!cmd->args || !cmd->args[0])
    {
        if (cmd->redirects)
            redirect = 0;
        else
            return (0);
    }
    pid = fork();
    if (pid < 0)
        return (perror("minishell: fork"), 1);
    if (pid == 0)
    {
        if (apply_redirections(cmd->redirects, redirect, *envp, 0) < 0)
            exit(1);
        if (is_builtin(cmd->args[0]))
            exit(exec_builtin(cmd, envp));
        execute_external(cmd, *envp);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

int execute_pipeline(t_cmd *cmd, char ***envp)
{
    int pipe_fd[2];
    int prev_fd;
    int num_cmds;
    int status;
    int last_status;
    pid_t pid;
    char *tmp_file;
    t_redir *redir;
    t_cmd *temp;

    prev_fd = -1;
    num_cmds = 0;
    last_status = 0;

    temp = cmd;
    while (temp)
    {
        redir = temp->redirects;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                tmp_file = read_heredoc(redir->file, 1, *envp, 0);
                
                redir->type = REDIR_IN;
                free(redir->file);
                redir->file = tmp_file;
            }
            redir = redir->next;
        }
        temp = temp->next;
    }
    while (cmd)
    {
        if (cmd->next)
            if (pipe(pipe_fd) < 0)
                return (perror("minishell: pipe"), 1);
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
            if (apply_redirections(cmd->redirects, 1, *envp, 0) < 0)
                exit(1);
            if (!cmd->args || !cmd->args[0])
                exit(0);
            if (is_builtin(cmd->args[0]))
                exit(exec_builtin(cmd, envp));
            execute_external(cmd, *envp);
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
        if (num_cmds == 1 && WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        num_cmds--;
    }
    return (last_status);
}
