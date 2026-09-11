
#include "arg.h"
#include "hlp.h"

bool	add_new_cmd(t_cmd *cmd, t_list **node)
{
	t_token	*tkn;
	t_list	*new_cmd;
	t_list	*last;

	tkn = (*node)->content;
	if (!exp_has_space(tkn->str))
		return (true);
	new_cmd = list_maker(tkn->str, true);
	if (new_cmd == NULL)
		return (false);
	last = lst_last(new_cmd);
	lst_mod_node(&cmd->lst, *node, new_cmd, free_token);
	*node = last->last;
	return (true);
}

bool	expand_cmd(t_cmd *cmd)
{
	t_token	*cur;
	t_list	*tmp;
	bool	expanded;

	tmp = cmd->lst;
	while (tmp != NULL)
	{
		cur = tmp->content;
		if (cur->type == tkn_command)
		{
			expanded = false;
			if (!env_expansion(&cur->str, &expanded, true))
				return (false);
			if (expanded && !add_new_cmd(cmd, &tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
