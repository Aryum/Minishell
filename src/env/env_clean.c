
#include "env.h"
#include "hlp.h"

void	env_clean(void)
{
	lst_clear(&(data_get()->env), env_clear_var);
}

