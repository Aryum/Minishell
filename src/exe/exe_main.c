
#include "exe.h"
#include "hlp.h"
#include <signal.h>

static bool	is_exe_parent(t_cmd *cmd)
{
	t_cmd_type	type;

	type = cmd->type;
	if (type == cmd_cd || type == cmd_exit || type == cmd_unset)
		return (true);
	if (type == cmd_export && cmd->arg_count > 1)
		return (true);
	return (false);
}

static void	wait_children(t_cmd **args)
{
	int	i;
	int	status;

	i = 0;
	set_sig_quit();
	while (args[i] != NULL)
	{
		if (args[i]->pid != -1)
		{
			waitpid(args[i]->pid, &status, 0);
			args[i]->pid = -1;
			if (WIFEXITED(status))
				env_set_error(WEXITSTATUS(status));
		}
		i++;
	}
	restore_si_gquit();
	close(data_get()->last_in);
}

void exe_main(t_cmd	**args)
{
	int	i;

	data_get()->cur_args = args;
	if (args[1] == NULL && is_exe_parent(args[0]) && args[0]->exec)
		args[0]->function(args[0]);
	else
	{
		i = 0;
		data_get()->last_in = dup(STDIN_FILENO);
		if (data_get()->last_in == -1)
			clean_exit_errno();
		while (args[i] != NULL)
		{
			exec_pipe(args[i]);
			i++;
		}
		wait_children(args);
	}
	clean_args();
}
