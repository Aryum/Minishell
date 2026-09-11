
#include "cmd.h"
#include "hlp.h"

static void	free_vars(char *cmd_path, char **env, char **env_split)
{
	free(cmd_path);
	lib_split_clean(env);
	lib_split_clean(env_split);
}

static void	exec(t_cmd *cmd, char *cmd_path, char **env)
{
	if (cmd_path == NULL)
		return ;
	if (execve(cmd_path, cmd->args, env) == -1)
	{
		err_perror(cmd->args[0]);
		env_set_error(errno);
	}
}

bool	exe_other(t_cmd *cmd)
{
	char	*cmd_path;
	char	**env;
	char	**env_split;
	char	*env_path;

	cmd_path = NULL;
	env_path = env_get_value("PATH");
	env_split = lib_split(env_path, ':');
	env = create_env(data_get()->env);
	if (env == NULL || (env_path != NULL && env_split == NULL))
		return (free_vars(cmd_path, env, env_split), false);
	if (!get_path(cmd->args[0], &cmd_path, env_split))
		return (free_vars(cmd_path, env, env_split), false);
	exec(cmd, cmd_path, env);
	return (free_vars(cmd_path, env, env_split), true);
}
