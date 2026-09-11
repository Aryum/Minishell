
#ifndef ENV_H
# define ENV_H

# include "../nullshell.h"

//clean
void		env_clean(void);

//create
bool		env_create(char **env);

//get
t_data		*data_get(void);
t_list		*env_get_node(char *key);
char		*env_get_value(char *key);
t_env_var	*env_get_content(char *key);

//mod
void		env_remove(char *str);
bool		env_mod_str(char *str);
bool		env_append_str(char *str);
bool		env_mod_key(char *key, char *value);
void		env_set_error(unsigned char value);
void		env_reset_error(void);
void		env_clear_var(void *in);
bool		env_add_var(t_env_var *var);

bool		env_add_entry(char *key, char *value);
bool		env_mod_entry(char *key, char *value);
bool		env_add_str_replace(char *str);
bool		env_add_str_append(char *str);

//expansion
char		*get_var_key(char *str, size_t *len);
bool		env_expansion(char **str, bool *expanded,bool check_quotes);

#endif