#ifndef MINISHELL_H
# define MINISHELL_H

# define MININAME "(*NULL)&hell"
# define CHECK_DIR "Invalid redirection, thats a no no for (*NULL)&hell!\n"
# define CHECK_QUOTES "Unclosed quotes, (*NULL)&hell doesnt like that!\n"
# define SYNTAX_ERROR   "syntax error near unexpected token"


# include <stdbool.h>
# include <stdio.h>
# include <unistd.h> 
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>

# include "../helpers/helpers.h"
# include "structs.h"
# include "parse/parse.h"
# include "data/data.h"
# include "env/env.h"
# include "arg/arg.h"
# include "exe/exe.h"
# include "command/cmd.h"
#endif