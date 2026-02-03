#include "minishell.h"

int g_signal = 0;

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
        printf("He escrito: %s\n", prompt);
        free(prompt);
    }
    return (0);
}