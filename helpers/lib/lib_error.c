
#include "lib.h"

void	lib_error(char *str)
{
	lib_putstr_fd("Error: ", 2);
	lib_putstr_fd(str, 2);
	lib_putstr_fd("\n", 2);
}
