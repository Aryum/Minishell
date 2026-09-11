
#include "lst.h"

int	lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = (*lst).next;
		i++;
	}
	return (i);
}
