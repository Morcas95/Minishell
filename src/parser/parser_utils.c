#include "minishell.h"

/*
 * Rellena de tokens un array hasta llegar al PIPE (sin contar redirecciones)
 * Retorna: El array
 * 
 * Fill a tokens' array until next PIPE (without redirections)
 * Returns: The tokens' array
 */
char **fill_args(t_token *tokens)
{
    int count;
    char **args;
    t_token *prev;

    prev = NULL;
    count = count_words_until_pipe(tokens);
    args = malloc((count + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    count = 0;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
            if (!prev || prev->type == TOKEN_WORD || prev->type == TOKEN_PIPE)
                args[count++] = strdup(tokens->value);
        prev = tokens;
        tokens = tokens->next;
    }
    args[count] = NULL;
    return (args);
}

/*
 * Cuenta el número de palabras hasta el siguiente PIPE o el final de los tokens
 * Retorna: El número de palabras.
 * 
 * Count number of WORDs until next PIPE or end of tokens
 * Returns: number of words
 */
int count_words_until_pipe(t_token *tokens)
{
    int count;
    t_token *prev;
    
    count = 0;
    prev = NULL;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
        {
            if (!prev || prev->type == TOKEN_WORD || prev->type == TOKEN_PIPE)
                count++;
        }
        prev = tokens;
        tokens = tokens->next;
    }
    return (count);
}


/*
 * Crea e inicializa una estructura de redirección
 * Retorna: Un puntero a la nueva redirección, o NULL en caso de eror
 * 
 * Create and initialize a redirection structure
 * Returns: pointer to new redir, or NULL on error
 */
t_redir *create_redir(t_redir_type type, char *file)
{
    t_redir *redir;
    
    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file = file;
    redir->next = NULL;
    return (redir);
}

t_redir_type token_to_redir_type(t_token_type type)
{
    if (type == TOKEN_REDIR_IN)
        return (REDIR_IN);
    if (type == TOKEN_REDIR_OUT)
        return (REDIR_OUT);
    if (type == TOKEN_REDIR_APPEND)
        return (REDIR_APPEND);
    return (REDIR_HEREDOC);
}

