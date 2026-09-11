
#include "lib.h"

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_tolower(int c)
{
	if (isclass(c, 'A', 'Z'))
		return (c + 32);
	return (c);
}
