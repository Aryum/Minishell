
#include "lib.h"

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_toupper(int c)
{
	if (isclass(c, 'a', 'z'))
		return (c - 32);
	return (c);
}
