
#include "env.h"
#include "hlp.h"

static char	*expand_var(char *str, size_t *last, size_t i)
{
	char	*temp;
	char	*var;
	char	*ret;
	size_t	var_len;

	var_len = 0;
	var = get_var_key(&(str[i]), &var_len);
	temp = lib_strdup_part(str, *last, i);
	ret = lib_strjoin(temp, var);
	free(temp);
	free(var);
	*last = i + var_len;
	return (ret);
}

static char	*append(char *str1, char *str2)
{
	char	*ret;

	if (str1 == NULL)
		ret = lib_strdup(str2);
	else
		ret = lib_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (ret);
}

static void	move_quotes(char *str, size_t *i, bool *flag, bool check_quotes)
{
	if (!check_quotes)
		return ;
	if (str[*i] == '\"')
		(*flag) = !(*flag);
	if (*flag)
		return ;
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
}

static bool	need_expansion(char *str, bool *expanded, bool *flag, bool check_quotes)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		move_quotes(str, &i, flag, check_quotes);
		if (lib_ischar(str[i], "$", 0))
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (false);
	if (expanded != NULL)
		*expanded = true;
	*flag = false;
	return (true);
}

bool	env_expansion(char **str, bool *expanded, bool check_quotes)
{
	size_t	i;
	size_t	last;
	char	*ret;
	bool	flag;

	flag = false;
	if (!need_expansion(*str, expanded, &flag, check_quotes))
		return (true);
	i = 0;
	ret = NULL;
	last = 0;
	while ((*str)[i] != '\0')
	{
		move_quotes(*str, &i, &flag, check_quotes);
		if ((*str)[i] == '$')
		{
			ret = append(ret, expand_var(*str, &last, i));
			if (ret == NULL)
				break ;
		}
		i++;
	}
	if (ret != NULL)
		ret = append(ret, lib_strdup_part(*str, last, i));
	return (free(*str), *str = ret, *str != NULL);
}
