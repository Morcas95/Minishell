#include "minishell.h"

/*
 * Parsear tokens a una estructura de comandos.
 * Retorna: el inicio de la lista de comandos, o NULL en caso de error.
 * 
 * Parse tokens into command structure.
 * Returns: head of command list, or NULL on error.
 */
t_cmd *parser(t_token *tokens)
{
    t_cmd *head;
    t_cmd *current;
    t_cmd *new_cmd;
    t_token *temp;
    
    head = NULL;
    current = NULL;
    temp = tokens;
    while (temp)
    {
        new_cmd = parse_one_cmd(temp);
        if (!head)
            head = new_cmd;
        else
            current->next = new_cmd;
        current = new_cmd;
        temp = next_pipe(temp);
        if (temp && temp->type == TOKEN_PIPE)
            temp = temp->next;
    }
    return (head);
}
/*
 * Busca el siguiente PIPE de la lista de tokens.
 * Retorna: el siguiente PIPE de la lista de tokens.
 * 
 * Find the next PIPE from the token list.
 * Returns: the next PIPE from the token list.
 */
t_token *next_pipe(t_token *tokens)
{
    while (tokens && tokens->type != TOKEN_PIPE)
        tokens = tokens->next;
    return (tokens);
}