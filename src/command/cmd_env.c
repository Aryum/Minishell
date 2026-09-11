
#include "cmd.h"
#include "hlp.h"

static void	iter_env(void *in)
{
	t_env_var	*val;

	val = (t_env_var *)in;
	if (val->value != NULL)
		printf("%s=%s\n", val->key, val->value);
}

bool	exe_env(t_cmd *cmd)
{
	if (cmd->arg_count > 1)
		err_agrs("env");
	else
		lst_iter(data_get()->env, iter_env);
	env_reset_error();
	return (true);
}
