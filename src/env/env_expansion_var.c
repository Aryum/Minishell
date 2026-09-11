
#include "env.h"
#include "hlp.h"

static bool	is_separator(char c)
{
	return (!(c == '_' || lib_isalnum(c)));
}

static char	*extract_key(char *str, size_t *len)
{
	char	*var;
	size_t	h;

	*len = str[1] == '?' || lib_isdigit(str[1]);
	if (!(*len))
	{
		while (str[*len + 1] != '\0' && !is_separator(str[*len + 1]))
			(*len)++;
	}
	var = lib_calloc(sizeof(char), *len + 1);
	if (var == NULL)
		return (NULL);
	h = 0;
	while (h < *len)
	{
		var[h] = str[h + 1];
		h++;
	}
	var[h] = '\0';
	return (var);
}

char	*get_var_key(char *str, size_t *len)
{
	char	*var;
	char	*ret;

	var = extract_key(str, len);
	*len += 1;
	if (var[0] == '\0')
	{
		if (!lib_ischar(str[1], "\"\'", 0))
			return (free(var), lib_strdup("$"));
		else
			return (free(var), lib_strdup(""));
	}
	if (var[0] == '?')
		return (free(var), lib_itoa(data_get()->error_val));
	ret = env_get_value(var);
	free(var);
	if (ret == NULL)
		return (lib_strdup(""));
	return (lib_strdup(ret));
}
