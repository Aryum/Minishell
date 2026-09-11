
#include "cmd.h"
#include "hlp.h"

static unsigned char	get_code(char *arg)
{
	size_t	i;
	char	ret;

	i = 0;
	ret = 0;
	if (lib_ischar(arg[i], "+-", 0))
		i++;
	while (arg[i] != '\0')
	{
		if (!lib_isdigit(arg[i]) || i > 20)
		{
			err_msg("exit", "numeric argument required");
			return (2);
		}
		ret = (arg[i] - '0') + ret * 10;
		i++;
	}
	if (arg[0] == '-')
		ret *= -1;
	return (ret);
}

bool	exe_exit(t_cmd *cmd)
{
	unsigned char	val;

	if (cmd->args[1] == NULL)
		val = data_get()->error_val;
	else
		val = get_code(cmd->args[1]);
	if (cmd->arg_count > 2 && val != 2)
	{
		err_agrs("exit");
		env_set_error(1);
	}
	else
	{
		print_fd(2, "%s says goodbye\n", MININAME);
		if (data_get()->error_val == 0)
			clean_exit(val);
		else
			clean_exit(data_get()->error_val);
	}
	return (true);
}
