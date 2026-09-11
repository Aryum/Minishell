
#ifndef HLP_H
# define HLP_H

# include "../nullshell.h"
# define ERR_HDOC "%s: warning: here doc delimited by eof (wanted `%s')\n"

//files hlp
bool	is_valid_file(char **str, bool *break_loop);

//files in
bool	hdoc_get_info(t_list *lst, t_hdoc *info);
bool	hdoc_set(t_rdir *in, t_hdoc *info);
bool	infile_check(t_rdir *in, char *name);
bool	set_infile(t_rdir *in);
bool	hdoc_read(char *eof, t_hdoc *hdoc);

//files out
bool	outfile_set(t_rdir *outfile, t_token *token);
bool	is_outfile(t_token *token);

//get cmd
bool	args_set_cmd(t_cmd *args);

//get rdir
bool	args_set_rdir(t_cmd *args);

//hlp
bool	exp_has_space(char *str);
bool	expand_cmd(t_cmd *cmd);
char	*remove_quotes(char *s);
void	str_pull_back(char *s);

#endif