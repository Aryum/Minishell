
#include "lst.h"

void	**lst_to_arr(t_list *lst)
{
	void **ret;
	int	i;
	int	size;

	size = lst_size(lst);
	ret = malloc((size + 1) * sizeof(void *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = lst->content;
		lst = lst->next;
		i++;
	}
	ret[size] = NULL;
	return (ret);
}
