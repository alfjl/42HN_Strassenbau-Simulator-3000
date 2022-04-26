#include "cub3d.h"

// unsigned int	color_convert(long color)
// {
// 	int	a;
// 	int	r;
// 	int	g;
// 	int	b;

// 	// a = ((color >> 48) & 0xFFFF) / 0xFF;
// 	a = 0;
// 	r = ((color >> 32) & 0xFFFF) / 0xFF;
// 	g = ((color >> 16) & 0xFFFF) / 0xFF;
// 	b = ((color) & 0xFFFF) / 0xFF;
// 	printf("a %d r %d g %d b %d\n", a, r, g, b);
// 	return (argb_create(r, g, b, a));
// }

unsigned int	argb_shade_color(int color, float brightness)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = ((color >> 24) & 0xFF);
	r = ((color >> 16) & 0xFF);
	g = ((color >> 8) & 0xFF);
	b = ((color) & 0xFF);
	return (argb_create(r * brightness, g * brightness, b * brightness, a));
}

unsigned int	rgba_create(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (a & 0xff));
}

unsigned int	argb_create(int r, int g, int b, int a)
{
	return (((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8)
		+ (b & 0xff));
}
