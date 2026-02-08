#include "minishell.h"

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
    
    // Ir al final de la lista
    current = cmd->redirects;
    while (current->next)
        current = current->next;
    
    current->next = new_redir;
}

/*
 * Parsear tokens a una estructura de comandos.
 * Retorna: el inicio de la lista de comandos, o NULL en caso de error.
 * 
 * Parse tokens into command structure.
 * Returns: head of command list, or NULL on error.
 */
t_cmd *parser(t_token *tokens)
{
    // TODO: implementar
    (void)tokens;
    return (NULL);
}