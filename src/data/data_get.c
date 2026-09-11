
#include "data.h"

t_data	*data_get(void)
{
	static t_data	ret;

	return (&ret);
}
