# include "cub3d.h"

int	game(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win3D, data()->imgs[BACKGROUND_IMG].ptr, 0, 0);
	// static_display_rays();
	// static_display_player();
	return (EXIT_SUCCESS);
}
