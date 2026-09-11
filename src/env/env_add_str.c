#include "env.h"
#include "hlp.h"

bool	extract_key(t_env_var *ret, char *str, size_t i)
{
	if (str[i] == '=' && str[i - 1] == '+')
		ret->key = lib_strdup_part(str, 0, i - 1);
	else
		ret->key = lib_strdup_part(str, 0, i);
	return (ret->key != NULL);
}

t_env_var	*extract_env_var(char *str)
{
	t_env_var	*ret;
	size_t	i;

	i = 0;
	ret = lib_calloc(1, sizeof(t_env_var));
	if (ret != NULL)
	{
		while (!lib_ischar(str[i], "=", 1))
			i++;
		if (!extract_key(ret, str, i))
			return (env_clear_var(ret), NULL);
		if (str[i] == '\0')
			return (ret);
		ret->value = lib_strdup(&str[i + 1]);
		if (ret->value == NULL)
			return (env_clear_var(ret), NULL);
	}
	return (ret);
}

bool	env_add_str_append(char *str)
{
	t_env_var	*new_var;
	t_env_var	*old_var;
	char	*tmp;

	new_var = extract_env_var(str);
	if (new_var == NULL)
		return (false);
	old_var = env_get_content(new_var->key);
	if (old_var == NULL)
		return (env_add_var(new_var));
	if (new_var->value == NULL)
		return (env_clear_var(new_var), true);
	if (old_var->value != NULL)
		tmp = lib_strjoin(old_var->value, new_var->value);
	else
		tmp = lib_strdup(new_var->value);
	free(old_var->value);
	old_var->value = tmp;
	return (env_clear_var(new_var), old_var->value != NULL);
}

bool	env_add_str_replace(char *str)
{
	t_env_var	*new_var;
	t_list		*lst;

	new_var = extract_env_var(str);
	if (new_var == NULL)
		return (false); 
	lst = env_get_node(new_var->key);
	if (lst == NULL)
		return (env_add_var(new_var));
	if (new_var->value == NULL)
		return (env_clear_var(new_var), true);
	env_clear_var(lst->content);
	lst->content = new_var;
	return (true);
}

bool	env_add_str_new(char *str)
{
	t_env_var	*new_var;

	new_var = extract_env_var(str);
	if (new_var == NULL)
		return (false); 
	return (env_add_var(new_var));
}
