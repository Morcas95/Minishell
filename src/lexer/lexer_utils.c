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
/*
 * Extrae el siguiente token del string empezando por el índice i.
 * Actualiza i a la posición después del token.
 * Retorna: el token, o NULL en caso de error.
 * 
 * Extract next token from string starting at index i.
 * Updates i to position after the token.
 * Returns: the token, or NULL on error.
 */
t_token *extract_token(char *str, int *i)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->next = NULL;
    token->value = NULL;  // Por defecto NULL
    
    if (str[*i] == '|')
    {
        token->type = TOKEN_PIPE;
        (*i)++;
    }
    else if (str[*i] == '<')
    {
        if (str[*i + 1] == '<')
        {
            token->type = TOKEN_HEREDOC;
            (*i) += 2;
        }
        else
        {
            token->type = TOKEN_REDIR_IN;
            (*i)++;
        }
    }
    else if (str[*i] == '>')
    {
        if (str[*i + 1] == '>')
        {
            token->type = TOKEN_REDIR_APPEND;
            (*i) += 2;
        }
        else
        {
            token->type = TOKEN_REDIR_OUT;
            (*i)++;
        }
    }
    return (token);
}

/*
 * Extrae una palabra (TOKEN_WORD) del string.
 * Gestiona las comillas y se para en los espacios u operadores.
 * Retorna: el string extraído, o NULL en caso de error.
 * 
 * Extract a word (TOKEN_WORD) from string.
 * Handles quotes and stops at spaces or operators.
 * Returns: the extracted string, or NULL on error.
 */
char *extract_word(char *str, int *i)
{
    // TODO: implement
    (void)str;
    (void)i;
    return (NULL);
}