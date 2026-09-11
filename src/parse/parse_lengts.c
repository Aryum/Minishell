
#include "parse.h"
#include "hlp.h"

size_t	arg_length(char *arg, size_t i)
{
	int		trigger;
	int		on_quotes;
	size_t	ret;

	on_quotes = 0;
	trigger = 0;
	ret = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] && is_sign(arg, i) && trigger == 0)
			return (ret);
		if (arg[i] == trigger && on_quotes == 1)
			on_quotes = update_trigger(0, &trigger);
		else if ((arg[i] == '\'' || arg[i] == '\"') && on_quotes == 0)
			on_quotes = update_trigger(arg[i], &trigger);
		if ((arg[i] == ' ' || arg[i] == '	') && trigger == 0)
			return (ret);
		i++;
		ret++;
	}
	return (ret);
}
