
#include "env.h"
#include "hlp.h"

static bool	update_values(void)
{
	char	*path;
	char	*lvl;
	bool	ret;

	lvl = lib_itoa(lib_atoi(env_get_value("SHLVL")) + 1);
	path = getcwd(NULL, 0);
	if (lvl == NULL || path == NULL)
		return (free(lvl), free(path), false);
	ret = env_mod_entry("SHLVL", lvl) && env_mod_entry("SHELL", path);
	return (free(lvl), free(path), ret);
}

static bool on_null_env(void)
{
	if (!env_add_entry("PWD", getcwd(NULL, 0)))
		return (false);
	if (!env_add_entry("SHLVL", "1"))
		return (false);
	if (!env_add_entry("_", "usr/bin/env"))
		return (false);
	return (true);
}

bool	env_create(char **env)
{
	int		i;

	i = 0;
	if (*env == NULL)
		return (on_null_env());
	while (env[i] != NULL)
	{
		if (!env_add_str_new(env[i]))
			return (env_clean(), false);
		i++;
	}
	return (update_values());
}
