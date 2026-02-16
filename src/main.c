#include "minishell.h"

int g_signal = 0;

/*
 * Process the input line
 * Tokenizes and prints tokens for debugging
 */
void process_input(char *input)
{
    t_token *tokens;
    t_cmd   *cmds;
    t_cmd   *current;
    int     i;

    if (!input || !*input)
        return ;
    tokens = lexer(input);
    if (!tokens)
        return ;
    cmds = parser(tokens);
    current = cmds;
    while (current)
    {
        printf("=== CMD ===\n");
        i = 0;
        while (current->args && current->args[i])
        {
            printf("  arg[%d]: %s\n", i, current->args[i]);
            i++;
        }
        current = current->next;
    }
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