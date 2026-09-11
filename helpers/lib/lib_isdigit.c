
static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isdigit(int c)
{
	if (isclass(c, '0', '9'))
		return (2048);
	return (0);
}
