#include "cub3d.h"

bool	is_wall(float y, float x)
{
	float	miny;
	float	maxy;
	float	minx;
	float	maxx;
	
	if (COLISSION == false)
		return (false);
	miny = y - DISTANCE;
	maxy = y + DISTANCE;
	minx = x - DISTANCE;
	maxx = x + DISTANCE;
	if (maxy < data()->map.height && miny >= 0 && maxx < data()->map.width && minx >= 0)
	{
		if (data()->map.grid[(int)miny][(int)minx] == WALL)
			return (true);
		if (data()->map.grid[(int)maxy][(int)maxx] == WALL)
			return (true);
		if (data()->map.grid[(int)miny][(int)maxx] == WALL)
			return (true);
		if (data()->map.grid[(int)maxy][(int)minx] == WALL)
			return (true);
		return (false);
	}
	return (true);
}
