
static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isascii(int c)
{
	if (isclass(c, 0, 127))
		return (1);
	return (0);
}
