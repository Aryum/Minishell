#include "arg.h"
#include "hlp.h"

bool	hdoc_get_info(t_list *lst, t_hdoc *info)
{
	t_token	*var;

	while (lst != NULL)
	{
		var = (t_token *)lst->content;
		if (var->type == tkn_in_hdoc)
		{
			free(info->str);
			info->str = lib_strdup("");
			if (!hdoc_read(var->str, info))
				return (false);
			if (info->eof_char)
				print_fd(2, ERR_HDOC, MININAME, var->str);
			info->is_last = true;
		}
		else if (var->type == tkn_in_files)
			info->is_last = false;
		lst = lst->next;
	}
	return (true);
}

bool	hdoc_set(t_rdir *in, t_hdoc *info)
{
	int	fd[2];

	in->set = false;
	if (pipe(fd) == -1)
		return (false);
	if (!info->eof_char)
		lib_putstr_fd(info->str, fd[1]);
	close (fd[1]);
	in->fd = fd[0];
	in->set = true;
	return (true);
}
