
#include "lib.h"

int	lib_ischar(char c, char *sep, int null)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (null && sep[i] == c);
}
