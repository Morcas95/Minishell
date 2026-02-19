#include "minishell.h"

int g_signal = 0;

/*
 * Process the input line
 * Tokenizes and prints tokens for debugging
 */
void process_input(char *input, char **envp)
{
    t_token *tokens;
    t_cmd   *cmds;
    int     exit_status;

    if (!input || !*input)
        return;
    tokens = lexer(input);
    if (!tokens)
        return;
    cmds = parser(tokens);
    if (!cmds)
        return;
    exit_status = execute(cmds, envp);
    printf("Exit status: %d\n", exit_status);
}

int main(int argc, char **argv, char **envp)
{
    char *prompt;

    (void)argc;
    (void)argv;

    setup_signals();
    
    while (1)
    {
        prompt = readline("minishell> ");
        if (!prompt)
        {
            break;
        }
        if (*prompt)
            add_history(prompt);
        process_input(prompt, envp);
    }
    free(prompt);
    return (0);
}