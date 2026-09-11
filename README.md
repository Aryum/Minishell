# Minishell

A simple shell implementation in C — your very own little Bash. This project explores processes, file descriptors, and how a command-line interpreter works under the hood.

## About

Minishell recreates the core experience of an interactive shell like `bash`. It parses and executes commands, handles quoting and environment variable expansion, supports redirections and pipes, implements a set of built-in commands, and reacts to signals the way a real shell does.

## Features

- Interactive **prompt** that waits for user input
- Working **history** via `readline`
- Executes commands found via `PATH`, or using a relative/absolute path
- **Quoting**
  - Single quotes (`'`) prevent all interpretation of metacharacters
  - Double quotes (`"`) prevent interpretation except for `$`
- **Redirections**
  - `<` input redirection
  - `>` output redirection
  - `<<` heredoc (reads until a line matching the delimiter is seen)
  - `>>` output redirection in append mode
- **Pipes** (`|`) chaining multiple commands together
- **Environment variable expansion** (`$VAR`)
- `$?` expands to the exit status of the last foreground pipeline
- Signal handling matching `bash` behavior:
  - `Ctrl-C` → new prompt on a new line
  - `Ctrl-D` → exits the shell
  - `Ctrl-\` → does nothing (interactive mode)
- **Built-in commands**
  - `echo` (with `-n` option)
  - `cd` (relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`



