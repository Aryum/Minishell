#ifndef CMD_H
# define CMD_H

# include "../nullshell.h"

//directory
bool	exe_pwd(t_cmd *cmd);
bool	exe_cd(t_cmd *cmd);

//echo
bool	exe_echo(t_cmd *cmd);

//env
bool	exe_env(t_cmd *cmd);
bool	exe_export(t_cmd *cmd);
bool	exe_unset(t_cmd *cmd);

//exit
bool	exe_exit(t_cmd *cmd);

//other
bool	exe_other(t_cmd *cmd);

#endif
