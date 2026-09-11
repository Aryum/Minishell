#include "arg.h"
#include "hlp.h"

bool	infile_check(t_rdir *in, char *name)
{
	in->set = false;
	if (access(name, R_OK) == -1)
		return (err_perror(name), false);
	in->set = true;
	in->val = name;
	return (true);
}

bool	set_infile(t_rdir *in)
{
	if (in->set)
	{
		in->fd = open(in->val, O_RDONLY, 0400);
		in->set = false;
		if (in->fd == -1)
			return (err_perror(in->val), false);
		in->set = true;
	}
	return (true);
}
