#include "arg.h"
#include "hlp.h"

static bool	check_files(t_token *var, t_cmd *args, bool *break_loop)
{
	if (is_outfile(var) || var->type == tkn_in_files)
	{
		if (!is_valid_file(&var->str, break_loop))
			return (false);
		if (!*break_loop)
		{
			if (var->type == tkn_in_files && !infile_check(args->in, var->str))
				*break_loop = true;
			if (is_outfile(var) && !outfile_set(args->out, var))
				*break_loop = true;
		}
	}
	return (true);
}

static bool	loop_rdirs(t_cmd *args)
{
	t_list	*temp;
	t_token	*var;
	bool	break_loop;

	break_loop = false;
	temp = args->lst;
	while (temp != NULL)
	{
		var = (t_token *)temp->content;
		if (!check_files(var, args, &break_loop))
			return (false);
		if (break_loop)
			break ;
		temp = temp->next;
	}
	if (break_loop)
		args->exec = false;
	return (true);
}

bool	args_set_rdir(t_cmd *args)
{
	t_hdoc	hdoc_info;
	bool	ret;

	ret = true;
	lib_memset(&hdoc_info, 0, sizeof(t_hdoc));
	if (!hdoc_get_info(args->lst, &hdoc_info))
		return (false);
	if (!loop_rdirs(args))
		return (free(hdoc_info.str), false);
	else if (args->exec)
	{
		if (hdoc_info.is_last)
			ret = hdoc_set(args->in, &hdoc_info);
		else
			ret = set_infile(args->in);
	}
	else
		env_set_error(1);
	return (free(hdoc_info.str), ret);
}
