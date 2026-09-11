
#include "lib.h"

int	lib_isalnum(int c)
{
	return (lib_isdigit(c) || lib_isalpha(c));
}
