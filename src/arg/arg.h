
#ifndef ARG_H
# define ARG_H

# include "../nullshell.h"

typedef struct s_hdoc
{
	char	*str;
	bool	eof_char;
	bool	is_last;
}	t_hdoc;

//args
t_cmd	*args_get(t_list **lst);
void	args_close(t_cmd *args);
void	free_token(void *ptr);
void	args_free(void *in);

#endif