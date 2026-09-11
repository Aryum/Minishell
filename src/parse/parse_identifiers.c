
#include "parse.h"
#include "hlp.h"

t_tkn_type	type_identifier(char *arg, size_t *i)
{
	if (arg[*i] == '>' && arg[*i + 1] == '>')
	{
		*i += 2;
		return (tkn_out_append);
	}
	else if (arg[*i] == '<' && arg[*i + 1] == '<')
	{
		*i += 2;
		return (tkn_in_hdoc);
	}
	else if (arg[*i] == '<')
	{
		*i += 1;
		return (tkn_in_files);
	}
	else if (arg[*i] == '>')
	{
		*i += 1;
		return (tkn_out_owrite);
	}
	return (tkn_command);
}

int	target(char *arg, size_t i)
{
	int	trigger;
	int	on_quotes;

	on_quotes = 0;
	trigger = 0;
	if (arg[i] && is_sign(arg, i) && trigger == 0)
		return (1);
	else if (arg[i] == trigger && on_quotes == 1)
		on_quotes = update_trigger(0, &trigger);
	else if ((arg[i] == '\'' || arg[i] == '\"') && on_quotes == 0)
		on_quotes = update_trigger(arg[i + 1], &trigger);
	if (is_sign(arg, i) && trigger == 0)
		return (1);
	else
		return (0);
}

int	spaces(char *arg, size_t i)
{
	int	trigger;
	int	on_quotes;

	on_quotes = 0;
	trigger = 0;
	if (arg[i] && (arg[i] == ' ' || arg[i] == '	') && trigger == 0)
		return (1);
	else if (arg[i] == trigger && on_quotes == 1)
		on_quotes = update_trigger(0, &trigger);
	else if ((arg[i] == '\'' || arg[i] == '\"') && on_quotes == 0)
		on_quotes = update_trigger(arg[i], &trigger);
	if ((arg[i] == ' ' || arg[i] == '	') && trigger == 0)
		return (1);
	else
		return (0);
}

int	invalid_characters(char *arg)
{
	int	trigger;
	int	on_quotes;
	int	i;

	on_quotes = 0;
	trigger = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] && (arg[i] == ';' || arg[i] == '\\') && trigger == 0)
			return (print_fd(2, "%s cant read (%c)\n", MININAME, arg[i]), 0);
		else if (arg[i] == trigger && on_quotes == 1)
			on_quotes = update_trigger(0, &trigger);
		else if ((arg[i] == '\'' || arg[i] == '\"') && on_quotes == 0)
			on_quotes = update_trigger(arg[i], &trigger);
		i++;
	}
	return (1);
}
