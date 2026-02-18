#ifndef MINISHELL_H
# define MINISHELL_H

#define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"

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

//* Redirection types
typedef enum e_redir_type
{
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // <<
}   t_redir_type;

//* Redirection structure
typedef struct s_redir
{
    t_redir_type    type;
    char            *file;          // Filename for redirection
    struct s_redir  *next;
}   t_redir;

//* Command structure
typedef struct s_cmd
{
    char            **args;         // Array of arguments [cmd, arg1, arg2, NULL]
    t_redir         *redirects;     // List of redirections
    struct s_cmd    *next;          // Next command (for pipes)
}   t_cmd;

//* Signals
void	handle_sigint(int sig);
void	setup_signals(void);

//* Lexer
t_token *lexer(char *input);
t_token *extract_token(char *str, int *i);
char    *extract_word(char *str, int *i);
int     extract_plain(const char *s, int *i, char **out);
int     extract_quoted(const char *s, int *i, char **out);
int     skip_spaces(char *str, int i);
int     is_operator(char c);

//* Parser
t_cmd *parser(t_token *tokens);
t_cmd *create_cmd(void);
t_cmd *parse_one_cmd(t_token *tokens);
t_redir *create_redir(t_redir_type type, char *file);
void add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);
int count_words_until_pipe(t_token *tokens);
char **fill_args(t_token *tokens);
t_token *next_pipe(t_token *tokens);
t_redir_type token_to_redir_type(t_token_type type);

//*Executor
int execute(t_cmd *cmd, char **envp);
int execute_simple(t_cmd *cmd, char **envp);
int execute_pipeline(t_cmd *cmd, char **envp);

//* Paths
int	resolve_via_path(const char *cmd, char **envp, char **out_path);
int	resolve_direct_path(const char *cmd, char **out_path);
const char	*get_env_value(char **envp, const char *key);
int	scan_dirs_tokens(char **dirs, size_t tokens, const char *cmd, char **out_path);
int	build_and_check(char *dir, const char *cmd, char **out_path);
char	*build_candidate(char *dir, const char *cmd);
int	has_slash(const char *s);

//* Redirections
int apply_redirections(t_redir *redirects);

#endif