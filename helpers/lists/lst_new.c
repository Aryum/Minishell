
#include "lst.h"

t_list	*lst_new(void *content)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (ret != NULL)
	{
		(*ret).content = content;
		(*ret).next = NULL;
		(*ret).last = NULL;
	}
	return (ret);
}
