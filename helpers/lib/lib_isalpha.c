
#include "lib.h"

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isalpha(int c)
{
	if (isclass(c, 'a', 'z') || isclass(c, 'A', 'Z'))
		return (1024);
	return (0);
}
