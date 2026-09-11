
#include "lib.h"

void	lib_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	write(fd, s, lib_strlen(s));
}
