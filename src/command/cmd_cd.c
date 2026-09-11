
#include "cmd.h"
#include "hlp.h"

static bool	change_dir(char *path, int *error)
{
	char	*old;
	char	*cur;
	bool	ret;

	ret = true;
	old = getcwd(NULL, 0);
	*error = chdir(path);
	cur = getcwd(NULL, 0);
	if (old == NULL || cur == NULL)
		ret = false;
	else if (!*error)
	{
		if (!env_mod_entry("OLDPWD", old) || !env_mod_entry("CUR", cur))
			ret = false;
	}
	return (free(old), free(cur), ret);
}

bool	exe_cd(t_cmd *cmd)
{
	char	*path;
	int		error;

	if (cmd->arg_count > 2)
		return (err_agrs("cd"), true);
	path = cmd->args[1];
	if (path == NULL)
		path = env_get_value("HOME");
	if (path == NULL)
		return (err_msg("cd", "HOME not set"), true);
	if (!change_dir(path, &error))
		return (false);
	if (error)
	{
		err_perror("cd");
		env_set_error(errno);
	}
	else
		env_reset_error();
	return (true);
}
