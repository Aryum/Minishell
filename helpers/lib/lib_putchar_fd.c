
#include "lib.h"

void	lib_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}
