#include "includes/minishell.h"
#include <stdio.h>
#include <string.h>

#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define YELLOW "\033[33m"
#define CYAN   "\033[36m"
#define RESET  "\033[0m"
#define BOLD   "\033[1m"

static int	g_passed = 0;
static int	g_failed = 0;

char	*append_char(char *result, char c);
char	*append_str(char *result, char *value);
char	*resolve_var(const char *line, int *i, char **envp, int last_exit_status);
void	write_expanded(int fd, char *expanded);

static void	check_str(const char *fn, const char *label,
				const char *got, const char *expected)
{
	int	ok;

	if (!got && !expected)
		ok = 1;
	else if (got && expected)
		ok = (strcmp(got, expected) == 0);
	else
		ok = 0;
	if (ok)
	{
		printf(GREEN "  [PASS]" RESET " %-20s %s\n", fn, label);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %-20s %s\n", fn, label);
		printf("         expected : \"%s\"\n", expected ? expected : "(null)");
		printf("         got      : \"%s\"\n", got      ? got      : "(null)");
		g_failed++;
	}
}

static char	*fake_env[] = {
	"HOME=/home/morcas",
	"USER=morcas",
	"SHELL=/bin/bash",
	"_EMPTY=",
	NULL
};

static char	*read_file(const char *path)
{
	FILE	*f;
	char	*buf;
	long	sz;

	f = fopen(path, "r");
	if (!f)
		return (NULL);
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	rewind(f);
	buf = malloc(sz + 1);
	if (!buf)
		return (fclose(f), NULL);
	fread(buf, 1, sz, f);
	buf[sz] = '\0';
	fclose(f);
	return (buf);
}

static int	feed_stdin(const char *lines)
{
	int		pipefd[2];
	int		saved;

	pipe(pipefd);
	write(pipefd[1], lines, strlen(lines));
	close(pipefd[1]);
	saved = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (saved);
}

static char	*run_heredoc(const char *input_lines, const char *delim)
{
	char	*tmpfile;
	char	*result;
	int		saved_stdin;

	saved_stdin = feed_stdin(input_lines);
	tmpfile = read_heredoc((char *)delim, 1, fake_env, 42);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	if (!tmpfile)
		return (NULL);
	result = read_file(tmpfile);
	unlink(tmpfile);
	free(tmpfile);
	return (result);
}

int	main(void)
{
	char	*s;
	int		i;
	char	*out;

	printf(BOLD CYAN "\n══ redirections tests ══\n\n" RESET);

	/* ── get_env_value ──────────────────────────────────────────────────── */
	printf(YELLOW BOLD "get_env_value\n" RESET);
	check_str("get_env_value", "HOME existe",
		(char *)get_env_value(fake_env, "HOME"), "/home/morcas");
	check_str("get_env_value", "USER existe",
		(char *)get_env_value(fake_env, "USER"), "morcas");
	check_str("get_env_value", "valor vacio",
		(char *)get_env_value(fake_env, "_EMPTY"), "");
	check_str("get_env_value", "clave inexistente → NULL",
		(char *)get_env_value(fake_env, "MISSING"), NULL);

	/* ── append_char ────────────────────────────────────────────────────── */
	printf(YELLOW BOLD "\nappend_char\n" RESET);
	s = ft_strdup("hel");
	s = append_char(s, 'l');
	check_str("append_char", "aniade un char", s, "hell");
	free(s);

	s = ft_strdup("");
	s = append_char(s, 'X');
	check_str("append_char", "aniade a string vacio", s, "X");
	free(s);

	s = ft_strdup("hi");
	s = append_char(s, ' ');
	check_str("append_char", "aniade un espacio", s, "hi ");
	free(s);

	/* ── append_str ─────────────────────────────────────────────────────── */
	printf(YELLOW BOLD "\nappend_str\n" RESET);
	s = ft_strdup("hello ");
	s = append_str(s, ft_strdup("world"));
	check_str("append_str", "junta dos strings", s, "hello world");
	free(s);

	s = ft_strdup("path=");
	s = append_str(s, ft_strdup("/home/morcas"));
	check_str("append_str", "junta valor de path", s, "path=/home/morcas");
	free(s);

	s = ft_strdup("abc");
	s = append_str(s, ft_strdup(""));
	check_str("append_str", "aniade string vacio", s, "abc");
	free(s);

	/* ── resolve_var ────────────────────────────────────────────────────── */
	printf(YELLOW BOLD "\nresolve_var\n" RESET);

	i = 0; s = resolve_var("?", &i, fake_env, 42);
	check_str("resolve_var", "$? → exit status (42)", s, "42");
	free(s);

	i = 0; s = resolve_var("HOME", &i, fake_env, 0);
	check_str("resolve_var", "variable HOME", s, "/home/morcas");
	free(s);

	i = 0; s = resolve_var("USER", &i, fake_env, 0);
	check_str("resolve_var", "variable USER", s, "morcas");
	free(s);

	i = 0; s = resolve_var("_EMPTY", &i, fake_env, 0);
	check_str("resolve_var", "variable con valor vacio", s, "");
	free(s);

	i = 0; s = resolve_var("1abc", &i, fake_env, 0);
	check_str("resolve_var", "digito tras $ → NULL", s, NULL);

	/* ── write_expanded ─────────────────────────────────────────────────── */
	printf(YELLOW BOLD "\nwrite_expanded\n" RESET);
	{
		char	tmp[] = "/tmp/.test_write_XXXXXX";
		int		fd;
		char	*result;

		fd = mkstemp(tmp);
		write_expanded(fd, ft_strdup("hello world"));
		close(fd);
		result = read_file(tmp);
		check_str("write_expanded", "escribe string en fd", result, "hello world");
		free(result);
		unlink(tmp);

		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write_expanded(fd, NULL);
		close(fd);
		result = read_file(tmp);
		check_str("write_expanded", "NULL → no escribe nada", result, "");
		free(result);
		unlink(tmp);
	}

	/* ── expand_heredoc_line / read_heredoc ─────────────────────────────── */
	printf(YELLOW BOLD "\nexpand_heredoc_line / read_heredoc\n" RESET);

	out = run_heredoc("hello\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "linea sin vars sin cambios", out, "hello\n");
	free(out);

	out = run_heredoc("$HOME\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "$HOME expandido", out, "/home/morcas\n");
	free(out);

	out = run_heredoc("soy $USER\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "var en medio de frase", out, "soy morcas\n");
	free(out);

	out = run_heredoc("code=$?\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "$? expandido a 42", out, "code=42\n");
	free(out);

	out = run_heredoc("$123\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "$ antes de digito → literal", out, "$123\n");
	free(out);

	out = run_heredoc("fin=$\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "$ al final → literal", out, "fin=$\n");
	free(out);

	out = run_heredoc("[$NOPE]\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "var inexistente → vacio", out, "[]\n");
	free(out);

	out = run_heredoc("hola\nsoy $USER en $HOME\nadios\nEOF\n", "EOF");
	check_str("expand_heredoc_line", "heredoc multilinea",
		out, "hola\nsoy morcas en /home/morcas\nadios\n");
	free(out);

	/* ── summary ────────────────────────────────────────────────────────── */
	printf(BOLD "\n══ Resultado: " GREEN "%d passed" RESET BOLD
		", " RED "%d failed" RESET BOLD " ══\n\n" RESET,
		g_passed, g_failed);
	return (g_failed > 0 ? 1 : 0);
}