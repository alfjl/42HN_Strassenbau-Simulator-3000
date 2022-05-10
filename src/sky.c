#include "cub3d.h"

int	get_sky_color(t_ray *ray, int y)
{
	int	tx;
	int	ty;

	if (!SKY_ENABLED)
		return (data()->map.ceiling.rgb);
	tx = ray->angle * (data()->imgs[SKY_IMG].width / (2 * M_PI));
	ty = y + data()->imgs[SKY_IMG].height / 4 - data()->player.dz;
	return (get_pixel_color(&data()->imgs[SKY_IMG], tx, ty));
}
