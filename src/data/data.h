
#ifndef DATA_H
# define DATA_H

# include "../nullshell.h"

t_data	*data_get(void);
void	clean_exit(unsigned char val);
void	clean_exit_errno(void);
void	clean_args(void);
void	err_perror(char *arg);
void	err_msg(char *arg, char *msg);
void	err_agrs(char *arg);
void	err_export(char *arg);
void setup_signals(void);
void	set_sig_quit(void);
void	restore_si_gquit(void);
#endif