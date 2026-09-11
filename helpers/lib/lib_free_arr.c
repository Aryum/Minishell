#include "lib.h"

void	lib_free_arr(void **arr, void (*del)(void*))
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		del(arr[i]);
		i++;
	}
	free(arr);
}