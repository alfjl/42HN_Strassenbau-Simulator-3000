#include "cub3d.h"

bool	is_wall(float y, float x)
{
	if (COLISSION == false)
		return (false);
	if (y < data()->map.height && x < data()->map.width)
	{
		if (data()->map.grid[(int)y][(int)x] != WALL)
			return (false);
	}
	return (true);
}
