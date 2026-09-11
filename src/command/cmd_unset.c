
#include "cmd.h"

bool	exe_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->arg_count)
	{
		env_remove(cmd->args[i]);
		i++;
	}
	env_reset_error();
	return (true);
}
