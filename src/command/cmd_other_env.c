
#include "cmd.h"
#include "hlp.h"

static int	count_env(t_list *env)
{
	t_env_var	*cur;
	int			ret;

	ret = 0;
	while (env != NULL)
	{
		cur = env->content;
		if (cur->value != NULL)
			ret++;
		env = env->next;
	}
	return (ret);
}

static char	*create_entry(t_env_var	*cur)
{
	char	*ret;
	char	*temp;

	temp = lib_strjoin(cur->key, "=");
	ret = lib_strjoin(temp, cur->value);
	free(temp);
	return (ret);
}

char	**create_env(t_list *env)
{
	t_env_var	*cur;
	char		**ret;
	int			count;
	int			i;

	count = count_env(env);
	ret = lib_calloc(count + 1, sizeof(char *));
	if (ret != NULL)
	{
		i = 0;
		while (i < count)
		{
			cur = env->content;
			if (cur->value != NULL)
			{
				ret[i] = create_entry(cur);
				if (ret[i] == NULL)
					return (lib_split_clean(ret), NULL);
				i++;
			}
			env = env->next;
		}
	}
	return (ret);
}
