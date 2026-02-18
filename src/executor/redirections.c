#include "minishell.h"

/*
 * Apply all redirections from command
 * Called in child process before execve
 * Returns: 0 on success, -1 on error
 */
int apply_redirections(t_redir *redirects)
{
    int fd;

    while (redirects)
    {
        if (redirects->type == REDIR_IN)
        {
            fd = open(redirects->file, O_RDONLY);
            if (fd == -1)
                return (perror("minishell: input"), -1);
            dup2(fd, 0);
            close(fd);
        }
        else if (redirects->type == REDIR_OUT)
        {
            fd = open(redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return (perror("minishell: output"), -1);
            dup2(fd, 1);
            close(fd);
        }
        else if (redirects->type == REDIR_APPEND)
        {
            fd = open(redirects->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (perror("minishell: append"), -1);
            dup2(fd, 1);
            close(fd);
        }
        redirects = redirects->next;
    }
    return (0);
}