
#include "parse.h"
#include "hlp.h"

t_token	*ini_token(t_tkn_type *type, char *str, size_t *i)
{
	t_token	*ret;
	int		len;

	ret = lib_calloc(1, sizeof(t_token));
	if (ret != NULL)
	{
		len = arg_length(str, *i);
		ret->str = lib_strdup_part(str, *i, *i + len);
		if (!ret->str)
			return (free_token(ret), NULL);
		ret->type = *type;
		*i += len;
		*type = tkn_command;
	}
	return (ret);
}

bool	add(t_list **ret, t_tkn_type *type, char *str, size_t *i)
{
	t_token	*token;
	t_list	*new_node;

	token = ini_token(type, str, i);
	if (!token)
		return (false);
	new_node = lst_new(token);
	if (!new_node)
		return (free_token(token), false);
	lst_add_back(ret, new_node);
	return (true);
}

t_list	*list_maker(char *arg, bool allcmd)
{
	t_list		*ret;
	t_tkn_type	type;
	size_t		i;
	size_t		leng;

	i = 0;
	leng = lib_strlen(arg);
	type = tkn_command;
	ret = NULL;
	while (i < leng)
	{
		if (arg[i] && !target(arg, i) && !spaces(arg, i))
		{
			if (!add(&ret, &type, arg, &i))
				return (lst_clear(&ret, free_token), NULL);
		}
		if (!allcmd && target(arg, i))
			type = type_identifier(arg, &i);
		if (arg[i] == ' ')
			i++;
	}
	return (ret);
}
