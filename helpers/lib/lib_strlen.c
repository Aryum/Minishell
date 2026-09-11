
#include "lib.h"

size_t	lib_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}
