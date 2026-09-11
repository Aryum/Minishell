
#include "data.h"

void	clean_args(void)
{
	t_cmd	**args;
	int	i;

	i = 0;
	args = data_get()->cur_args;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		args_close(args[i]);
		args_free(args[i]);
		i++;
	}
	free(data_get()->cur_args);
	data_get()->cur_args = NULL;
}

void	clean_exit(unsigned char val)
{
	clean_args();
	env_clean();
	rl_clear_history();
	exit(val);
}

void	clean_exit_errno(void)
{
	clean_args();
	env_clean();
	rl_clear_history();
	perror("ERROR: ");
	exit(errno);
}