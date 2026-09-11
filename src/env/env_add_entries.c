
#include "env.h"
#include "hlp.h"

t_env_var	*env_create_var(char *key, char *value)
{
	t_env_var	*ret;

	ret = lib_calloc(1, sizeof(t_env_var));
	if (ret == NULL)
		return (NULL);
	ret->key = lib_strdup(key);
	ret->value = lib_strdup(value);
	if (ret->key == NULL || ret->value == NULL)
		return (env_clear_var((t_env_var *)ret), NULL);
	return (ret);
}

bool	env_add_var(t_env_var *var)
{
	t_list		*temp;

	temp = lst_new((void *)var);
	if (temp == NULL)
		return (false);
	lst_add_back(&(data_get()->env), temp);
	return (true);
}

bool	env_add_entry(char *key, char *value)
{
	t_env_var	*content;

	content = env_create_var(key, value);
	if (content == NULL)
		return (false);
	return (env_add_var(content));
}

bool	env_mod_entry(char *key, char *value)
{
	t_list		*node;
	t_env_var	*var;

	node = env_get_node(key);
	if (node == NULL)
		return (env_add_entry(key, value));
	var = (t_env_var *)(node->content);
	free(var->value);
	var->value = lib_strdup(value);
	return (var->value == NULL);
}


