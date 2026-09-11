
#ifndef PARSE_H
# define PARSE_H

# include "../nullshell.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**pipe_split(char *s);
t_list	*list_maker(char *argument, bool allcmd);
int		parse_check_rdir(char *s);
int		parse_check_quotes(char *s);
int		only_signals(char *s);
int		invalid_characters(char *argument);
int		is_valid_input(char *line);
void	setup_signals(void);
#endif
