
#include "arg.h"
#include "hlp.h"

t_cmd	*args_get(t_list **lst)
{
	t_cmd	*ret;

	if (lst == NULL)
		return (NULL);
	ret = lib_calloc(1, sizeof(t_cmd));
	if (ret != NULL)
	{
		ret->pid = -1;
		ret->exec = true;
		ret->lst = *lst;
		ret->in = lib_calloc(1, sizeof(t_rdir));
		ret->out = lib_calloc(1, sizeof(t_rdir));
		if (ret->in == NULL || ret->out == NULL)
			return (args_free(ret), NULL);
		if (!args_set_rdir(ret))
			return (args_free(ret), NULL);
		if (!args_set_cmd(ret))
			return (args_free(ret), NULL);
	}
	return (ret);
}
