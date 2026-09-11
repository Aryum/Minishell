
#include "cmd.h"
#include "hlp.h"

static t_add_mode	get_add_mode(char *id)
{
	int	i;

	i = 0;
	if (lib_isdigit(id[0]) || (!lib_isalpha(id[0]) && id[0] != '_'))
		return (error);
	while (id[i] != '\0' && id[i] != '=')
	{
		if (id[i] == '+' && id[i + 1] == '=')
			return (append_var);
		else if (id[i] != '_' && !lib_isalnum(id[i]))
			return (error);
		i++;
	}
	return (overwrite_var);
}

static bool	add_to_env(t_cmd *cmd)
{
	t_add_mode	mode;
	int			i;
	bool		reset_err;

	i = 1;
	reset_err = true;
	while (cmd->args[i] != NULL)
	{
		mode = get_add_mode(cmd->args[i]);
		if (mode == error)
		{
			err_export(cmd->args[i]);
			env_set_error(1);
			reset_err = false;
		}
		if (mode == append_var && !env_add_str_append(cmd->args[i]))
			return (false);
		if (mode == overwrite_var && !env_add_str_replace(cmd->args[i]))
			return (false);
		i++;
	}
	if (reset_err)
		env_reset_error();
	return (true);
}

bool	exe_export(t_cmd *cmd)
{
	if (cmd->arg_count == 1)
		export_print(cmd);
	else if (!add_to_env(cmd))
		return (false);
	return (true);
}
