
#include "env.h"
#include "hlp.h"

static int	compare(void *target, void *node)
{
	t_env_var	*var;
	char		*str;

	str = (char *)target;
	var = (t_env_var *)node;
	return (lib_strncmp(var->key, str, lib_strlen(var->key)) == 0);
}

t_list	*env_get_node(char *key)
{
	if (key == NULL || key[0] == '\0')
		return (NULL);
	return (lst_get_node(data_get()->env, (void *)key, compare));
}

t_env_var	*env_get_content(char *key)
{
	t_list	*node;

	if (key == NULL || key[0] == '\0')
		return (NULL);
	node = lst_get_node(data_get()->env, (void *)key, compare);
	if (node != NULL)
		return ((t_env_var *)node->content);
	return (NULL);
}

char	*env_get_value(char *key)
{
	t_list	*lst;

	lst = env_get_node(key);
	if (lst == NULL)
		return (NULL);
	return (((t_env_var *)(lst->content))->value);
}
