#ifndef MINISHELL_H
# define MINISHELL_H

#define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern int	g_signal;

//* Tokens Types
typedef enum e_token_type
{
    TOKEN_WORD,         // Normal Word
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_REDIR_APPEND, // >>
    TOKEN_HEREDOC       // <<
}   t_token_type;

//* Tokens Structure
typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;

//* Signals
void	handle_sigint(int sig);
void	setup_signals(void);

t_token *lexer(char *input);
int skip_spaces(char *str, int i);
int is_operator(char c);

#endif