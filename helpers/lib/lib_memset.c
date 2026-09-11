
#include "lib.h"

void	*lib_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (s);
}
