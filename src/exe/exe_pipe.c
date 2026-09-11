
#include "exe.h"
#include "hlp.h"

static void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	set_rdir(t_cmd *args, int *in, int *out, int fd[2])
{
	*in = data_get()->last_in;
	*out = -1;
	if (args->in->set)
		*in = args->in->fd;
	if (args->out->set)
		*out = args->out->fd;
	else if (!args->is_last)
		*out = fd[1];
}

void fuck(int d)
{
	exit (d);
}

static void	exec_child(t_cmd *args, int fd[2])
{
	int	in;
	int	out;
	int	i;

	i = 0;
	set_rdir(args, &in, &out, fd);
	if (dup2(in, STDIN_FILENO) == -1)
		clean_exit_errno();
	if (out != -1 && dup2(out, STDOUT_FILENO) == -1)
		clean_exit_errno();
	close_pipe(fd);
	close(data_get()->last_in);
	while (data_get()->cur_args[i] != NULL)
	{
		args_close(data_get()->cur_args[i]);
		i++;
	}
	if (args->exec && !args->function(args))
		clean_exit_errno();
	clean_exit(data_get()->error_val);
}

void	exec_pipe(t_cmd *args)
{
	int	fd[2];
	
	if (pipe(fd) == -1)
		clean_exit_errno();
	if(args->exec)
	{
		args->pid = fork();
		if (args->pid == -1)
		{
			close_pipe(fd);
			clean_exit_errno();
		}
	}
	if (args->pid == 0)
		exec_child(args, fd);
	else
	{
		close(data_get()->last_in);
		data_get()->last_in = fd[0];
		close(fd[1]);
	}
}
