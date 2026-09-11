
#include "lib.h"

void	lib_putendl_fd(char *s, int fd)
{
	if (fd >= 0 && s != NULL)
	{
		write(fd, s, lib_strlen(s));
		write(fd, "\n", 1);
	}
}
