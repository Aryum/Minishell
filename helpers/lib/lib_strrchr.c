
#include "lib.h"

char	*lib_strrchr(const char *s, int c)
{
	size_t	i;

	i = lib_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)&(s[i]));
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)&(s[i]));
	return (NULL);
}
