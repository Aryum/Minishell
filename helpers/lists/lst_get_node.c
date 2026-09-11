
#include "lst.h"

t_list	*lst_get_node(t_list *lst, void *content, int(*func)(void *, void *))
{
	while (lst != NULL)
	{
		if (func(content, lst->content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
