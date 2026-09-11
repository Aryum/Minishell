
#include "lib.h"

void	lib_bzero(void *s, size_t n)
{
	lib_memset(s, '\0', n);
}
