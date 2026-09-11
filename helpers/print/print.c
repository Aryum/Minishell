
#include "print.h"

static void	formatstr(t_buf *buf, char c, va_list args, int *ctr)
{
	if (c == 'c')
		h_put_char(buf, va_arg(args, int), ctr);
	else if (c == 's')
		h_put_str(buf, va_arg(args, char *), ctr);
	else if (c == 'p')
		h_put_ptr(buf, va_arg(args, void *), ctr);
	else if (c == 'd' || c == 'i')
		h_put_int(buf, va_arg(args, int), ctr);
	else if (c == 'u')
		h_put_uint(buf, va_arg(args, unsigned int), ctr);
	else if (c == 'x')
		h_put_uintbase(buf, va_arg(args, unsigned int), "0123456789abcdef", ctr);
	else if (c == 'X')
		h_put_uintbase(buf, va_arg(args, unsigned int), "0123456789ABCDEF", ctr);
	else if (c == '%')
		h_put_char(buf, '%', ctr);
	else
		*ctr = -1;
}

static void	loop_str(t_buf *buf, const char *str, va_list arg_v, int *ret)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			h_put_char(buf, str[i], ret);
		else
		{
			formatstr(buf, str[i + 1], arg_v, ret);
			if (*ret != -1)
				i++;
			else
				break ;
		}
		i++;
	}
}
int	print_fd(int fd, const char *str, ...)
{
	int		ret;
	va_list	arg_v;
	t_buf	buf;

	if (str == NULL || write(fd, 0, 0) == -1)
		return (-1);
	ret = 0;
	h_memset(&buf, 0, sizeof(t_buf));
	buf.fd = fd;
	va_start(arg_v, str);
	loop_str(&buf, str, arg_v, &ret);
	va_end(arg_v);
	h_put_buf(&buf);
	return (ret);
}

int	print(const char *str, ...)
{
	int		ret;
	va_list	arg_v;
	t_buf	buf;

	if (str == NULL || write(1, 0, 0) == -1)
		return (-1);
	ret = 0;
	h_memset(&buf, 0, sizeof(t_buf));
	buf.fd = 1;
	va_start(arg_v, str);
	loop_str(&buf, str, arg_v, &ret);
	va_end(arg_v);
	h_put_buf(&buf);
	return (ret);
}
