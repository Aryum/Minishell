
#include "cmd.h"
#include "hlp.h"

bool	exe_pwd(t_cmd *cmd)
{
	static char	*success_dir;
	char		dir[PATH_MAX];

	(void) cmd;
	if (success_dir == NULL)
		success_dir = env_get_value("PWD");
	if (getcwd(dir, PATH_MAX) != NULL)
		success_dir = &dir[0];
	printf("%s\n", success_dir);
	env_reset_error();
	return (true);
}
