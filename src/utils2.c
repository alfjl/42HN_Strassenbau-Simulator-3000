#include "cub3d.h"

double	pythagoras_hypotenuse(double a, double b)
{
	return (sqrt(a * a	+ b * b));
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}
