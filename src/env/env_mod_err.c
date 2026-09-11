
#include "env.h"
#include "hlp.h"

void	env_set_error(unsigned char value)
{
	data_get()->error_val = value;
}

void	env_reset_error(void)
{
	return (env_set_error(0));
}
