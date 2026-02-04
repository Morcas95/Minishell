#include "minishell.h"

/*
 * Salta espacios y tabs.
 * Retorna: el índice del primer carácter no-espacio.
 * 
 * Skips spaces and tabs.
 * Returns: the non-space first character.
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