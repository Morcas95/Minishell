#include "minishell.h"

int g_signal = 0;

/*
 * Process the input line
 * Tokenizes and prints tokens for debugging
 */
void process_input(char *input)
{
    t_token *tokens;
    t_token *current;
    
    if (!input || !*input)
        return;
    
    // Tokenizar
    tokens = lexer(input);
    if (!tokens)
    {
        printf("Error: lexer failed\n");
        return ;
    }
    
    // Imprimir tokens (debug)
    printf("\n=== TOKENS ===\n");
    current = tokens;
    while (current)
    {
        printf("Type: %d, Value: '%s'\n", 
            current->type, current->value ? current->value : "NULL");
        current = current->next;
    }
    printf("==============\n\n");
    
    // TODO: liberar tokens
}

int main(int argc, char **argv, char **envp)
{
    char *prompt;

    (void)argc;
    (void)argv;
    (void)envp;

    setup_signals();
    
    while (1)
    {
        prompt = readline("minishell> ");
        if (!prompt)
            break;
        if (*prompt)
            add_history(prompt);
        process_input(prompt);
        free(prompt);
    }
    return (0);
}