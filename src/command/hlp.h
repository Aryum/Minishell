
#ifndef HLP_H
# define HLP_H

# include <linux/limits.h>
# include "../nullshell.h"

# define NOFDIR_ERROR "No such file or directory"
# define NOCMD_ERROR "command not found"
# define ISDIR_ERROR "Is a directory"
# define PERM_ERROR "Permission denied"

typedef enum e_add_mode
{
	append_var,
	overwrite_var,
	error
}	t_add_mode;

bool	export_print(t_cmd *args);
char	**create_env(t_list *env);
bool	get_path(char *cmd, char **path, char **env_paths);

#endif