
#include "parse.h"
#include "hlp.h"

int	is_valid_rdir(char *s, int i)
{
	if (s[i] == '<' && s[i + 1] == '>')
		return (0);
	if (s[i] == '>' && s[i + 1] == '<')
		return (0);
	if (s[i] == '(' && s[i + 1] == ')')
		return (0);
	return (1);
}

int only_spaces(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if ((s[i] != ' ' || s[i] != '	' ) && s[i] != '\0')
			return (0);
		i++;
	}
	return(1);
}

int check_pipe_quotes(char *s)
{
	int		i;
	char	type;

	i = 0;
	type = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			type = s[i];
			i++;
			while (s[i] && (s[i] != type))
				i++;
			if (s[i] == '\0')
				return (print_fd(2, "%s", CHECK_QUOTES), 0);
			type = 0;
		}
		if ((s[i] == '|' && only_spaces(&s[i + 1])) || (s[i] == '|' && s[i + 1] == '|'))
			return(print_fd(2, "%s : %s \'%c\'\n", MININAME, SYNTAX_ERROR, s[i]),0);
		i++;
	}
	return(1);
}


int	is_valid_input(char *line)
{
	if(!check_pipe_quotes(line))
		return(0);
	if (!parse_check_rdir(line))
		return (print_fd(2, "%s", CHECK_DIR), 0);
	if (!invalid_characters(line))
		return (0);
	if (!only_signals(line))
		return (0);
	return (1);
}
