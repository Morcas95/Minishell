#include "minishell.h"

/*
 * Convierte un string en una lista de tokens
 * Retorna: la lista de tokens, o NULL si hay error
 * 
 * Converts a string into a tokens list
 * Returns: The tokens list, or NULL if there's an error
 */
t_token *lexer(char *input)
{
    t_token *head;
    t_token *current;
    t_token *new_token;
    int i;

    if (!input || !*input)
        return (NULL);
    head = NULL;
    current = NULL;
    i = 0;
    while (input[i])
    {
        i = skip_spaces(input, i);
        if (!input[i])
            break;
        new_token = extract_token(input, &i);
        if (!new_token)
            return (NULL);  // TODO: liberar lista si error
        if (!head)
            head = new_token;
        else
            current->next = new_token;
        current = new_token;
    }
    return (head);
}
