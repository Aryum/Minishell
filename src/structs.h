
#ifndef STRUCTS_H
# define STRUCTS_H

#include "nullshell.h"



//parse
typedef enum e_tkn_type
{
    tkn_in_files,
    tkn_in_hdoc,
    tkn_out_append,
    tkn_out_owrite,
    tkn_command,

} t_tkn_type;

typedef struct s_token
{
    t_tkn_type type;
    char *str;

}   t_token;

typedef enum	e_cmd_type
{
	cmd_cd,
	cmd_echo,
	cmd_env,
	cmd_exit,
	cmd_export,
	cmd_pwd,
	cmd_unset,
	cmd_other,
}	t_cmd_type;

typedef struct s_rdir
{
	char	*hdoc_file;
	char	*hdoc_value;
	char	*val;
	bool	set;
	int		fd;
	bool	is_hdoc;
}	t_rdir;

typedef struct s_cmd
{
	t_list		*lst;
	t_rdir		*in;
	t_rdir		*out;
	char		**args;
	t_cmd_type	type;
	pid_t		pid;
	int			arg_count;
	bool		is_last;
	bool		exec;
	bool		(*function)(struct s_cmd *);
}	t_cmd;

//env
typedef struct s_data
{
	t_cmd			**cur_args;
	t_list			*env;
	unsigned char	error_val;
	int				last_in;
	struct sigaction	sig_ign;
	struct sigaction	sig_kill;
}	t_data;

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

#endif