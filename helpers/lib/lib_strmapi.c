

#include "lib.h"

char	*lib_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	ret = lib_strdup(s);
	i = 0;
	if (ret != NULL && f != NULL)
	{
		while (ret[i] != '\0')
		{
			ret[i] = f(i, ret[i]);
			i++;
		}
	}
	return (ret);
}
