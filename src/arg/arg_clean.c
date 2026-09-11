
#include "arg.h"
#include "hlp.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	free(token->str);
	free(token);
}

void	args_free(void *in)
{
	t_cmd	*args;

	args = in;
	if (args != NULL)
	{
		if (args->args != NULL)
			free(args->args);
		if (args->in != NULL && args->in->is_hdoc)
			free(args->in->hdoc_file);
		free(args->in);
		free(args->out);
		lst_clear(&args->lst, free_token);
		free(args);
	}
}

void	args_close(t_cmd *args)
{
	if (args->in->set)
		close(args->in->fd);
	if (args->out->set)
		close(args->out->fd);
	args->in->set = false;
	args->out->set = false;
}
