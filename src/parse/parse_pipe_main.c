
#include "parse.h"
#include "hlp.h"

char	**pipe_split(char *s)
{
	int		i;
	int		s_i;
	int		cmd_count;
	char	**mat;

	i = 0;
	s_i = 0;
	cmd_count = command_count(s);
	mat = lib_calloc(sizeof(char *), (cmd_count + 1));
	if (!mat)
		return (NULL);
	while (i < cmd_count)
	{
		mat[i] = cmd_creator(s, &s_i);
		i++;
	}
	mat[i] = NULL;
	return (mat);
}
