
#include "data.h"

void	err_msg(char *arg, char *msg)
{
	print_fd(2, "%s: %s: %s\n", MININAME, arg, msg);
}

void	err_agrs(char *arg)
{
	err_msg(arg, "too many arguments\n");
}
void	err_export(char *arg)
{
	print_fd(2, "%s: export: `%s': not a valid identifier\n", MININAME, arg);
}

static void	fill_buffer(char *buffer, char * msg, int *start)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		buffer[*start +  i] = msg[i];
		i++;
	}
	buffer[*start +  i] = '\0';
	*start += i;
}

void	err_perror(char *arg)
{
	char	buffer[1024];
	int		i;

	i = 0;
	fill_buffer(buffer, MININAME, &i);
	fill_buffer(buffer, ": ", &i);
	fill_buffer(buffer, arg, &i);
	perror(buffer);
}
