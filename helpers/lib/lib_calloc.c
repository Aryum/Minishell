

#include "lib.h"

void	*lib_calloc(size_t nmemb, size_t size)
{
	void	*retval;
	size_t	totalsize;

	totalsize = nmemb * size;
	if (size > 0 && totalsize / size != nmemb)
		return (malloc(0));
	retval = malloc(totalsize);
	if (retval != NULL)
		lib_bzero(retval, totalsize);
	return (retval);
}
