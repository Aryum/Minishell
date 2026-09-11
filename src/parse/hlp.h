
#ifndef HLP_H
# define HLP_H

# include "../nullshell.h"

void		identifier(char *s, int i);
int			is_sign(char *s, int i);
int			update_trigger(char c, int *trigger);
int			command_leng(char *s, int i);
int			command_count(char *s);
char		*cmd_creator(char *s, int *s_i);
int			is_valid_rdir(char *s, int i);
t_tkn_type	type_identifier(char *argument, size_t *i);
size_t		arg_length(char *argument, size_t i);
int			target(char *argument, size_t i);
t_token		*ini_token(t_tkn_type *type, char *str, size_t *i);
int			spaces(char *argument, size_t i);
void		meu_sigint_handler(int sig);
void		setup_signals(void);
int			is_valid_rdir(char *s, int i);

#endif
