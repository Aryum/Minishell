
#include "lst.h"

t_list	*lst_last(t_list *lst)
{
	if (lst != NULL)
	{
		while ((*lst).next != NULL)
			lst = (*lst).next;
	}
	return (lst);
}
