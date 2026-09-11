#include "arg.h"
#include "hlp.h"

void	str_pull_back(char *s)
{
	int	i;

	i = 1;
	while (s[i] != '\0')
	{
		s[i - 1] = s[i];
		i++;
	}
	s[i - 1] = s[i];
}

char	*remove_quotes(char *s)
{
	char	flag;
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (lib_ischar(s[i], "\"\'", 0))
		{
			flag = s[i];
			str_pull_back(&s[i]);
			while (s[i] != flag)
				i++;
			str_pull_back(&s[i]);
		}
		if (!lib_ischar(s[i], "\"\'", 0))
			i++;
	}
	return (s);
}

bool	exp_has_space(char *str)
{
	size_t	i;
	char	flag;

	i = 0;
	while (str[i] != '\0')
	{
		if (lib_ischar(str[i], "\"\'", 0))
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
				i++;
			flag = '\0';
		}
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_file(char **str, bool *break_loop)
{
	char	*temp;

	temp = lib_strdup(*str);
	if (temp == NULL || !env_expansion(str, NULL, true))
		return (false);
	if (exp_has_space(*str))
	{
		*break_loop = true;
		err_msg(temp, "ambiguous redirect");
	}
	else
		remove_quotes(*str);
	return (free(temp), true);
}
