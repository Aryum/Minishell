
#include "lst.h"

void	lst_add_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = lst_last(*lst);
		(*last).next = new;
		(*new).last = last;
	}
}
