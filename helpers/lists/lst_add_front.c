
#include "lst.h"

void	lst_add_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		(*new).next = (*lst);
		(**lst).last = new;
		*lst = new;
	}
}
