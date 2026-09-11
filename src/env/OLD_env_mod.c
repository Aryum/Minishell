
#include "env.h"
#include "hlp.h"

static bool	env_add_entry(char *key, char *value)
{
	t_list	*temp;

	temp = lst_new((void *)env_create_var(str));
	if (temp == NULL)
		return (false);
	lst_add_back(&(data_get()->env), temp);
	return (true);
}

void	env_remove(char *str)
{
	t_env_var	*var;
	t_list		*node;

	node = env_get_node(str);
	var = node->content;
	if (var->key[0] == '_' && var->key[1] == '\0')
		return ;
	if (node != NULL)
		lst_delone(&(data_get()->env), node, env_clear_var);
}

bool	env_append_str(char *str)
{
	t_env_var	*var;
	t_list		*node;
	char		*temp;
	int			i;

	node = env_get_node(str);
	if (node == NULL)
		return (env_add_entry(str));
	i = 0;
	var = (t_env_var *)(node->content);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	temp = lib_strjoin(var->value, remove_quotes(&str[i + 1]));
	free(var->value);
	var->value = temp;
	return (var->value != NULL);
}

bool	env_mod_str(char *str)
{
	t_env_var	*var;
	t_list		*node;
	size_t		len;

	len = 0;
	node = env_get_node(str);
	if (node == NULL)
		return (env_add_entry(str));
	while (str[len] != '\0' && str[len] != '=')
		len++;
	if (str[len] == '\0')
		return (true);
	len++;
	var = (t_env_var *)(node->content);
	free(var->value);
	var->value =  lib_strdup(remove_quotes(&str[len]));
	return (var->value ==  NULL);
}

bool	env_mod_key(char *var, char *value)
{
	char	*eq;
	char	*val;

	eq = lib_strjoin(var, "=");
	if (eq == NULL)
		return (false);
	val = lib_strjoin(eq, value);
	free(eq);
	if (val == NULL)
		return (false);
	env_mod_str(val);
	free(val);
	return (true);
}
