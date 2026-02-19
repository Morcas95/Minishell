#include "minishell.h"

char *read_heredoc(char *delimiter)
{
    int fd;
    char *prompt;
    char *filename;

    filename = ft_strdup("/tmp/.heredoc_minishell");
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (free(filename), NULL);
    while (1)
    {
        prompt = readline("> ");
        if (!prompt || ft_strcmp(prompt, delimiter) == 0)
        {
            free(prompt);
            break;
        }
        write(fd, prompt, strlen(prompt));
        write(fd, "\n", 1);
        free(prompt);
    }
    close(fd);
    return (filename);
}

/*
 * Apply all redirections from command
 * Called in child process before execve
 * Returns: 0 on success, -1 on error
 */
int apply_redirections(t_redir *redirects)
{
    int fd;
    char *tmp_file;

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
        else if (redirects->type == REDIR_HEREDOC)
        {
            tmp_file = read_heredoc(redirects->file);
            if (!tmp_file)
                return (-1);
            fd = open(tmp_file, O_RDONLY);
            if (fd == -1)
            {
                free(tmp_file);
                return (perror("minishell: heredoc"), -1);
            }
            dup2(fd, 0);
            close(fd);
            unlink(tmp_file);
            free(tmp_file);
        }
        redirects = redirects->next;
    }
    return (0);
}