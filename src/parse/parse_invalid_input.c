
#include "parse.h"
#include "hlp.h"

int	parse_check_rdir(char *s)
{
	int		i;
	int		count;
	int		trigger;
	char	c;

	i = 0;
	count = 0;
	trigger = 0;
	c = 0;
	while (s[i])
	{
		if (is_sign(s, i) && trigger == 0)
			c = s[i];
		if (is_sign(s, i) && s[i] == c)
			count++;
		if (s[i] != c)
		{
			count = 0;
			trigger = 0;
		}
		if (count == 3 || !is_valid_rdir(s, i))
			return (0);
		i++;
	}
	return (1);
}

void	check_rdir(char *s, int i)
{
	int	l;

	l = i + 1;
	if (lib_ischar(s[l], " 	", 0))
	{
		while (s[l] == ' ' || s[l] == '	')
			l++;
		if (!is_sign(s, l) && s[l] != '|')
			return ;
	}
	if ((s[i] == '<' && s[i + 1] == '\0') || \
		((s[i] == '<' && s[i + 1] == '<' ) && s[i + 2] == '\0'))
		print_fd(2, "%s : %s \'newline\'\n", MININAME, SYNTAX_ERROR);
}

void	error_c(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_sign(s, i) || s[i] == '|')
			return (check_rdir(s, i));
		i++;
	}
}

int	only_signals(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (s[i])
	{
		if (s[i + 1] == '\0' && flag == 1)
			return (error_c(s), 0);
		if (!is_sign(s, i) && (s[i] != ' ' && s[i] != '	'))
			flag = 0;
		i++;
	}
	return (1);
}
