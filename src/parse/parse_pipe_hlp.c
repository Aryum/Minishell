
#include "parse.h"
#include "hlp.h"

int	is_sign(char *s, int i)
{
	if (s[i] == '<' && s[i + 1] != '>')
		return (1);
	else if (s[i] == '>' && s[i + 1] != '<')
		return (1);
	return (0);
}

int	update_trigger(char c, int *trigger)
{
	*trigger = c;
	return (c != 0);
}

int	command_leng(char *s, int i)
{
	int	trigger;
	int	on_quotes;
	int	ret;

	on_quotes = 0;
	trigger = 0;
	ret = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == trigger && on_quotes == 1)
			on_quotes = update_trigger(0, &trigger);
		else if ((s[i] == '\'' || s[i] == '\"') && on_quotes == 0)
			on_quotes = update_trigger(s[i], &trigger);
		if (s[i] == '|' && trigger == 0)
			return (ret);
		i++;
		ret++;
	}
	return (ret);
}

int	command_count(char *s)
{
	int	i;
	int	count;
	int	trigger;
	int	on_quotes;

	i = 0;
	on_quotes = 0;
	count = 1;
	trigger = 0;
	while (s[i])
	{
		if (s[i] == trigger && on_quotes == 1)
			on_quotes = update_trigger(0, &trigger);
		else if ((s[i] == '\'' || s[i] == '\"') && on_quotes == 0)
			on_quotes = update_trigger(s[i], &trigger);
		if (s[i] == '|' && trigger == 0)
			count++;
		i++;
	}
	return (count);
}

char	*cmd_creator(char *s, int *s_i)
{
	int		i;
	int		cmd_leng;
	char	*mat;

	i = 0;
	cmd_leng = command_leng(s, *s_i);
	mat = lib_calloc(sizeof(char), (cmd_leng + 1));
	if (!mat)
		return (0);
	while (i < cmd_leng)
	{
		mat[i] = s[*s_i];
		(*s_i)++;
		i++;
	}
	(*s_i)++;
	mat[i] = '\0';
	return (mat);
}
