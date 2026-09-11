# include "src/nullshell.h"
#pragma region 
void guh(void *ptr)
{
	t_token *token = (t_token *)ptr;
	char *type;
	switch (token->type)
	{
		case tkn_in_files:
			type = "Input";
			break;
		case tkn_in_hdoc:
			type = "Heredoc";
			break;
		case tkn_command:
			type = "Command";
			break;
		case tkn_out_append:
			type = "Append";
			break;
		case tkn_out_owrite:
			type = "Overwrite";
			break;
	}
	printf("	Type: %s\n	Value: %s\n\n", type, token->str);
}

void debug(t_cmd **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		printf("Args %d\n", i);
		lst_iter(args[i]->lst, guh);
		i++;
	}
	printf("______________________________________\n");
}
#pragma endregion
t_cmd **alloc_cmd_arr(char **matrix)
{
	t_cmd	**ret;
	t_list	*lst;
	int i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i] != NULL)
		i++;
	ret = lib_calloc(i + 1, sizeof(t_cmd));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		lst = list_maker(matrix[i], false);
		ret[i] = args_get(&lst);
		if (ret[i] == NULL)
			return (lib_free_arr((void **)ret, args_free), NULL);
		ret[i]->is_last = matrix[i + 1] == NULL;
		i++;
	}
	return (ret);
}

void	read_input(char *line)
{
	char	**pipes;
	t_cmd	**args;

	if (is_valid_input(line))
	{
		pipes = pipe_split(line);
		args = alloc_cmd_arr(pipes);
		lib_split_clean(pipes);
		if (args == NULL)
			clean_exit_errno();
		//debug(args);
		exe_main(args);
	}
}

int main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	env_create(env);
	setup_signals();
	while (1)
	{
		line = readline("(*NULL)&hell -> ");
		if (line == NULL)
			break ;
		else
			add_history(line);
		read_input(line);
		free(line);
	}
	print_fd(2, "%s says goodbye\n", MININAME);
	clean_exit(data_get()->error_val);
}