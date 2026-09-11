
static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isprint(int c)
{
	if (isclass(c, 32, 126))
		return (16384);
	return (0);
}
