
#include "arg.h"
#include "hlp.h"

static void	update_cmd_vars(t_cmd *arg, t_cmd_type type, bool (*f)(t_cmd *))
{
	arg->type = type;
	arg->function = f;
}

static void	set_func(t_cmd *cmd)
{
	char	*cmd_str;

	cmd_str = cmd->args[0];
	if (!lib_strncmp(cmd_str, "pwd", 4))
		update_cmd_vars(cmd, cmd_pwd, exe_pwd);
	else if (!lib_strncmp(cmd_str, "cd", 3))
		update_cmd_vars(cmd, cmd_cd, exe_cd);
	else if (!lib_strncmp(cmd_str, "echo", 5))
		update_cmd_vars(cmd, cmd_echo, exe_echo);
	else if (!lib_strncmp(cmd_str, "env", 4))
		update_cmd_vars(cmd, cmd_env, exe_env);
	else if (!lib_strncmp(cmd_str, "export", 7))
		update_cmd_vars(cmd, cmd_export, exe_export);
	else if (!lib_strncmp(cmd_str, "unset", 6))
		update_cmd_vars(cmd, cmd_unset, exe_unset);
	else if (!lib_strncmp(cmd_str, "exit", 5))
		update_cmd_vars(cmd, cmd_exit, exe_exit);
	else
		update_cmd_vars(cmd, cmd_other, exe_other);
}

static int	get_cmd_count(t_list *lst)
{
	t_token	*var;
	int		ret;

	ret = 0;
	while (lst != NULL)
	{
		var = (t_token *)lst->content;
		if (var->type == tkn_command)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

bool	args_set_cmd(t_cmd *args)
{
	t_token	*var;
	int		i;
	t_list	*lst;

	i = 0;
	if (!expand_cmd(args))
		return (false);
	lst = args->lst;
	args->arg_count = get_cmd_count(lst);
	args->args = lib_calloc(args->arg_count + 1, sizeof(char *));
	if (args->args == NULL)
		return (false);
	while (i < args->arg_count)
	{
		var = (t_token *)lst->content;
		if (var->type == tkn_command)
		{
			args->args[i] = remove_quotes(var->str);
			i++;
		}
		lst = lst->next;
	}
	if (args->args[0] == NULL)
		return (args->exec = false, true);
	return (set_func(args), true);
}
