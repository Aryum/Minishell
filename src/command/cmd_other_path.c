
#include "cmd.h"
#include "hlp.h"

static void	rm_extra_bars(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i] || !s[i + 1])
		return ;
	while (s[i] == '/' && s[i + 1] == '/')
		i++;
	while (s[i])
	{
		if (s[i] == '/' && s[i + 1] == '/')
			rm_extra_bars(&s[i]);
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = '\0';
}

static bool	check_raw_path(char *cmd, bool *is_abs, char **path)
{
	struct stat	inf;
	size_t		len;

	len = lib_strlen(cmd);
	*path = NULL;
	*is_abs = true;
	if (cmd[len - 1] == '/')
	{
		if (stat(cmd, &inf) != 0)
		{
			if (errno == ENOMEM)
				return (false);
			if (errno == EACCES)
				return (err_msg(cmd, PERM_ERROR), env_set_error(126), true);
		}
		if (S_ISDIR(inf.st_mode))
			return (err_msg(cmd, ISDIR_ERROR), env_set_error(126), true);
		else
			return (err_msg(cmd, NOFDIR_ERROR), env_set_error(127), true);
	}
	rm_extra_bars(cmd);
	if (access(cmd, F_OK) == 0)
		return (*path = lib_strdup(cmd), *path != NULL);
	*is_abs = cmd[0] == '.';
	return (true);
}

static bool	valid_path(char *cur_dir, char *cmd, size_t *start)
{
	size_t	i;
	size_t	size;

	size = 0;
	*start = lib_strlen(cmd);
	while (*start - size != 0 && cmd[*start - size - 1] != '/')
		size++;
	*start = *start - size;
	if (*start == 0)
		return (true);
	i = 0;
	while (cur_dir[i] != '\0')
	{
		if (cur_dir[i] == '/')
		{
			if (lib_strncmp(&cur_dir[i], cmd, size) == 0)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	join_path(char *cmd, char **path, char *cur_env_path)
{
	size_t	start;
	char	*cur_dir;

	start = 0;
	if (valid_path(cur_env_path, cmd, &start))
	{
		cur_dir = lib_strjoin(cur_env_path, "/");
		*path = lib_strjoin(cur_dir, &cmd[start]);
		free(cur_dir);
		if (*path == NULL)
			return (false);
		if (access(*path, F_OK) == 0)
			return (true);
		free(*path);
	}
	return (*path = NULL, true);
}

bool	get_path(char *cmd, char **path, char **env_paths)
{
	size_t	i;
	bool	is_abs;

	i = 0;
	is_abs = false;
	if (cmd[0] == '\0')
	{
		err_msg("\'\'", NOCMD_ERROR);
		return (env_set_error(127), *path = NULL, true);
	}
	if (!check_raw_path(cmd, &is_abs, path) || is_abs)
		return (is_abs);
	while (env_paths[i] != NULL)
	{
		if (!join_path(cmd, path, env_paths[i]))
			return (false);
		if (*path != NULL)
			return (true);
		i++;
	}
	err_msg(cmd, NOCMD_ERROR);
	return (env_set_error(127), *path = NULL, true);
}
