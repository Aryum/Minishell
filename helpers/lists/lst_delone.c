
#include "lst.h"

void	lst_delone(t_list **start, t_list *node, void (*del)(void*))
{
	if (start != NULL && *start != NULL && node != NULL && del != NULL)
	{
		if (*start == node)
			*start = (**start).next;
		if (node->last != NULL)
			node->last->next = node->next;
		if (node->next != NULL)
			node->next->last = node->last;
		del(node->content);
		free (node);
	}
}
