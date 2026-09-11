
#include "arg.h"
#include "hlp.h"

bool	is_outfile(t_token *token)
{
	t_tkn_type	t;

	t = token->type;
	return (t == tkn_out_append || t == tkn_out_owrite);
}

bool	outfile_set(t_rdir *outfile, t_token *token)
{
	outfile->set = false;
	if (outfile->set)
		close(outfile->fd);
	if (token->type == tkn_out_append)
		outfile->fd = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		outfile->fd = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (outfile->fd == -1)
		return (err_perror(token->str), false);
	outfile->set = true;
	return (true);
}
