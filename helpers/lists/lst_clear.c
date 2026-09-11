
#include "lst.h"

static void	clear(t_list **current, void (*del)(void*))
{
	if ((**current).next != NULL)
		clear(&((**current).next), del);
	del((**current).content);
	free (*current);
}

void	lst_clear(t_list **lst, void (*del)(void*))
{
	if (lst != NULL && *lst != NULL && del != NULL)
	{
		clear(lst, del);
		*lst = NULL;
	}
}
