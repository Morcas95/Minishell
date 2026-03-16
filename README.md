# Minishell

*This project has been created as part of the 42 School curriculum by maalonso and dcerezo-.*

## Description

Minishell is a simplified Unix shell implementation that replicates the core functionality of bash. This project demonstrates fundamental concepts in shell design, process management, and command-line parsing.

### Objective

The goal of Minishell is to build a working shell that:
- **Parses and executes** user commands with proper argument handling
- **Manages processes** through forking, executing, and waiting
- **Implements built-in commands** (echo, cd, pwd, export, unset, env, exit)
- **Handles I/O redirection** (input `<`, output `>`, append `>>`, heredoc `<<`)
- **Supports piping** (`|`) between multiple commands
- **Expands environment variables** (including `$VAR` and special variables like `$?`)
- **Manages signals** properly (CTRL+C, CTRL+D behavior)
- **Maintains memory** integrity without leaks

### Overview

Minishell reads commands from standard input, tokenizes and parses them, manages their execution (including I/O redirection and piping), and displays results. It provides an interactive shell experience similar to bash while implementing a simplified subset of its features.

## Instructions

### Compilation

To compile the project, use the provided Makefile:

```bash
make
```

This command will:
- Compile the libft library (custom C library with utility functions)
- Compile all source files in `src/` directory
- Link everything together to create the `minishell` executable

#### Additional Makefile targets:

```bash
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Recompile from scratch
```

### Installation

No installation is required. The compiled executable can be run directly from the project directory.

### Execution

Run the shell with:

```bash
./minishell
```

Once started, you can:
- **Enter commands**: Type any command (built-in or external)
- **Use pipes**: Chain commands with `|` (e.g., `cat file.txt | grep pattern`)
- **Redirect I/O**: Use `>`, `>>`, `<` for file redirection
- **Use heredoc**: Apply `<<` for multi-line input
- **Expand variables**: Reference environment variables with `$VAR` or `$?` for exit status
- **Exit**: Type `exit` or press CTRL+D to leave the shell

#### Example Commands:

```bash
minishell> echo Hello, World!
Hello, World!

minishell> pwd
/home/user/minishell

minishell> cd ..
minishell> export MYVAR=value
minishell> echo $MYVAR
value

minishell> cat file.txt | grep keyword
minishell> ls -la > output.txt
minishell> cat << EOF
> Type here
> Multiple lines
> EOF
```

#### Built-in Commands:

- **echo [-n]**: Print text (with optional -n flag to suppress newline)
- **cd [path]**: Change current directory
- **pwd**: Print working directory
- **export [var=value]**: Set or modify environment variables
- **unset [var]**: Remove environment variables
- **env**: Display all environment variables
- **exit [status]**: Exit the shell with optional status code

### Dependencies

Minishell requires:
- Unix-like operating system (Linux, macOS)
- GCC compiler
- GNU Readline library (for interactive prompt)
- POSIX-compliant system

## Resources

### Classic References

- **The Linux Programming Interface** by Michael Kerrisk - Comprehensive guide to system programming
- **Unix System Programming** by W. Richard Stevens and Stephen A. Rago - Deep dive into process management
- **Advanced Programming in the Unix Environment** - Standard reference for shell and process internals
- **Bash Manual** (https://www.gnu.org/software/bash/manual/) - Official bash documentation
- **POSIX Shell Command Language** - Standard shell specification
- **Man pages**: `man bash`, `man execve`, `man fork`, `man pipe`, `man dup2` - Essential Unix documentation

### Project Structure

```
minishell/
├── src/                    # Main source code
│   ├── main.c             # Entry point and main loop
│   ├── builtins/          # Built-in command implementations
│   ├── executor/          # Command execution and process management
│   ├── lexer/             # Tokenization and parsing
│   ├── parser/            # Command structure parsing
│   ├── memory/            # Memory management and cleanup
│   ├── signals/           # Signal handling (SIGINT, EOF)
│   └── shell_welcome/     # Welcome banner
├── libft/                 # Custom C library with utility functions
├── includes/              # Header files
├── Makefile               # Build configuration
└── README.md              # This file
```

### AI Usage

AI tools were used in the following capacities during this project:

1. **Code Debugging and Optimization** - Assistance in identifying memory leaks, segmentation faults, and process management issues
2. **Function Refactoring** - Suggestions for improving code structure and reducing redundancy in parsing and execution functions
3. **Implementation Guidance** - Support in understanding complex system calls (fork, execve, dup2, pipe) and their proper usage
4. **Error Handling** - Recommendations for proper error handling and edge case management in shell commands
5. **Documentation and Comments** - Help structuring code documentation and clarifying implementation details
