
#include "print.h"

void	h_put_ptr(t_buf *b, void *ptr, int *counter)
{
	if (ptr == NULL)
		h_put_str(b, "(nil)", counter);
	else
	{
		h_put_str(b, "0x", counter);
		h_put_ulongbase(b, (unsigned long)ptr, "0123456789abcdef", counter);
	}
}
