
#include "lib.h"

size_t	lib_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	retval;

	i = 0;
	retval = lib_strlen(src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (retval);
}
