
#include "env.h"
#include "hlp.h"

void	env_remove(char *key)
{
	t_list	*node;

	if (key[0] == '_' && key[1] == '\0')
		return ;
	node = env_get_node(key);
	if (node != NULL)
		lst_delone(&(data_get()->env), node, env_clear_var);
}

void	env_clear_var(void *in)
{
	t_env_var	*val;

	val = (t_env_var *)in;
	free(val->key);
	free(val->value);
	free(val);
}
