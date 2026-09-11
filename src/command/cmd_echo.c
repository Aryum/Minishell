
#include "cmd.h"
#include "hlp.h"

static bool	has_flag(char *str)
{
	size_t	i;

	i = 1;
	if (str == NULL)
		return (false);
	if (str[0] != '-')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	exe_echo(t_cmd *cmd)
{
	bool	flag;
	int		i;

	flag = has_flag(cmd->args[1]);
	i = 1 + flag;
	while (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	env_reset_error();
	return (true);
}
