
#include "data.h"

static void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);    // limpa a linha atual
	rl_on_new_line();          // move para nova linha
	rl_redisplay();            // mostra o novo prompt
	env_set_error(130);
}

static void	kill_childs(int sig)
{
	t_cmd  **args;
	int	i;

	(void)sig;
	i = 0;
	args = data_get()->cur_args;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		if (args[i]->pid != -1)
			kill(args[i]->pid, SIGKILL);
		i++;
	}
	print_fd(2,"Quit (core dumped)\n");
}

void setup_signals(void)
{
	struct sigaction	sig_int;

	sig_int.sa_handler = sigint_handler;
	data_get()->sig_kill.sa_handler = kill_childs;
	data_get()->sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&data_get()->sig_kill.sa_mask);
	sigemptyset(&data_get()->sig_ign.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	data_get()->sig_kill.sa_flags = SA_RESTART;
	data_get()->sig_ign.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &data_get()->sig_ign, NULL);
}

void	set_sig_quit(void)
{
	sigaction(SIGQUIT, &data_get()->sig_kill, NULL);
}

void	restore_si_gquit(void)
{
	sigaction(SIGQUIT, &data_get()->sig_ign, NULL);
}

