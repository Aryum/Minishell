
#ifndef HLP_H
# define HLP_H

# include "../nullshell.h"

char		*get_var_key(char *str, size_t *len);
t_env_var	*env_create_var(char *key, char *value);
bool		env_add_entry(char *key, char *value);
bool		env_add_str_new(char *str);

#endif