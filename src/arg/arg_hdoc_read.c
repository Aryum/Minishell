
#include "arg.h"
#include "hlp.h"

static char	*append_line(char *last, char *line)
{
	char	*temp;
	char	*ret;

	temp = lib_strjoin(line, "\n");
	free(line);
	if (last == NULL)
		ret = temp;
	else
	{
		ret = lib_strjoin(last, temp);
		free(temp);
		free(last);
	}
	return (ret);
}

static void	update_eof(char *str)
{
	char	flag;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && lib_ischar(str[i + 1], "\"\'", 0))
			str_pull_back(&str[i]);
		if (lib_ischar(str[i], "\"\'", 0))
		{
			flag = str[i];
			i++;
			while (str[i] != flag && str[i] != '\0')
				i++;
			flag = '\0';
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	remove_quotes(str);
}

static bool	check_quotes(char *eof)
{
	size_t	i;
	bool	ret;

	i = 0;
	ret = false;
	while (eof[i] != '\0')
	{
		if (lib_ischar(eof[i], "\"\'", 0))
		{
			ret = true;
			update_eof(eof);
			break ;
		}
		i++;
	}
	return (ret);
}

static void	free_vars(char *ret, char *line)
{
	free(line);
	free(ret);
}

bool	hdoc_read(char *eof, t_hdoc *hdoc)
{
	size_t	len;
	char	*line;
	bool	quotes;

	quotes = check_quotes(eof);
	len = lib_strlen(eof);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (errno == ENOMEM)
				return (free_vars(hdoc->str, line), false);
			else
				return (free(line), hdoc->eof_char = true, true);
		}
		if (!lib_strncmp(eof, line, len))
			break ;
		hdoc->str = append_line(hdoc->str, line);
		if (hdoc->str == NULL)
			break ;
	}
	if (!quotes)
		env_expansion(&hdoc->str, NULL, false);
	return (free(line), hdoc->str != NULL);
}
