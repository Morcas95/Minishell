#include "minishell.h"

/*
 * Crea e parsea una estructura de comando
 * Retorna: La estructura de comando.
 * 
 * Create and parse a command structure
 * Returns: The command structure
 */
t_cmd *parse_one_cmd(t_token *tokens)
{
    t_cmd *cmd;
    t_redir_type type;
    t_redir *redir;
    
    cmd = create_cmd();
    if (!cmd)
    return (NULL);
    cmd->args = fill_args(tokens);
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_PIPE)
        {
            if (!tokens->next)
                {
                    free(cmd->args);
                    free(cmd);
                    return(NULL);
                }
            type = token_to_redir_type(tokens->type);
            redir = create_redir(type, ft_strdup(tokens->next->value));
            add_redir_to_cmd(cmd, redir);
        }
        tokens = tokens->next;
    }
    return (cmd);
}

/*
 * Añadir redirección a la lista de redirecciones del comando
 *
 * Add redirection to command's redirection list
 */
void add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
    t_redir *current;
    
    if (!cmd->redirects)
    {
        cmd->redirects = new_redir;
        return;
    }
    current = cmd->redirects;
    while (current->next)
        current = current->next;
    current->next = new_redir;
}

/*
 * Crea e inicializa una estructura vacía de comandos
 * Retorna: un puntero al nuevo comando, o NULL en caso de error.
 * 
 * Create and initialize an empty command structure
 * Returns: pointer to new command, or NULL on error
 */
t_cmd *create_cmd(void)
{
    t_cmd *cmd;
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->redirects = NULL;
    cmd->next = NULL;
    return (cmd);
}