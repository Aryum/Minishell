
#include "cmd.h"
#include "hlp.h"

static void	swap(t_env_var **str1, t_env_var **str2)
{
	t_env_var	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static bool	is_lower(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] < str2[i]);
		i++;
	}
	return (false);
}

static void	sort(t_env_var **argv)
{
	int	i;
	int	h;

	i = 0;
	while (argv[i] != NULL)
	{
		h = 0;
		while (argv[h] != NULL)
		{
			if (is_lower(argv[i]->key, argv[h]->key))
				swap(&argv[i], &argv[h]);
			h++;
		}
		i++;
	}
}

bool	export_print(t_cmd *cmd)
{
	t_env_var	**arr;
	int			i;

	(void)cmd;
	arr = (t_env_var **)lst_to_arr(data_get()->env);
	if (arr == NULL)
		return (false);
	sort(arr);
	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i]->key[0] != '_' && arr[i]->key[1] != '\0')
		{
			printf("declare -x %s", arr[i]->key);
			if (arr[i]->value != NULL)
				printf("=\"%s\"", arr[i]->value);
			printf("\n");
		}
		i++;
	}
	free(arr);
	env_reset_error();
	return (true);
}
