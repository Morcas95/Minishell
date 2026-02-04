#include "minishell.h"

/*
 * Salta espacios y tabs.
 * Retorna: el índice del primer carácter no-espacio.
 * 
 * Skips spaces and tabs.
 * Returns: the first non-space character index.
 */
int skip_spaces(char *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    return (i);
}

/*
 * Comprueba si el carácter es un operador.
 * Retorna: 1 si es un operador, 0 si no.
 * 
 * Check if character is an operator.
 * Returns: 1 if operator, 0 if not.
 */
int is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

t_token *extract_token(char *str, int *i)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if(!token)
        return (NULL);
    token->next = NULL;
    if (str[*i] == '|')
    {
        token->type = TOKEN_PIPE;
        token->value = NULL;
        (*i)++;
    }
    else if (str[*i] == '<')
    {
        if (str[*i + 1] == '<')
        {
            token->type = TOKEN_HEREDOC;
            token->value = "<<";
            *i = *i + 2;
        }
        else
        {
            token->type = TOKEN_REDIR_IN;
            token->value = '<';
            (*i)++;
        }
    }
    else if (str[*i] == '>')
    {
        if (str[*i + 1] == '>')
        {
            token->type = TOKEN_REDIR_APPEND;
            token->value = ">>";
            *i = *i + 2;
        }
        else
        {
            token->type = TOKEN_REDIR_OUT;
            token->value = '>';
            (*i)++;
        }
    }
    return (token);
}