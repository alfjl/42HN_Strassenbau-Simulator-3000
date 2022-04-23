#include "cub3d.h"

static void	minimap_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	mlx_put_image_to_window(mlx, win, imgs[MINIMAP_IMG].ptr, MINIMAP_OFFSET,
		MINIMAP_OFFSET);
	mlx_put_image_to_window(mlx, win, imgs[PLAYER_IMG].ptr,
		MINIMAP_OFFSET + MINIMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2,
		MINIMAP_OFFSET + MINIMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2);
	my_destroy_image(mlx, &imgs[MINIMAP_IMG]);
	imgs[MINIMAP_IMG].ptr = NULL;
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	if (HAS_ALPHA)
		mlx_put_image_to_window(mlx, win, imgs[BACKGROUND_IMG].ptr, 0, 0);
	mlx_put_image_to_window(mlx, win, imgs[WALLS_IMG].ptr, 0, 0);
	my_destroy_image(mlx, &imgs[WALLS_IMG]);
}

static void	window_set_up(void)
{
	void	*mlx;
	void	*win;
	t_img	*imgs;

	mlx = data()->mlx;
	win = data()->win;
	imgs = data()->imgs;
	environment_to_window_buffer(mlx, win, imgs);
	if (MINIMAP)
		minimap_to_window_buffer(mlx, win, imgs);
	fps_to_window_buffer(); //remove
}

static void	static_get_mouse_info(t_buttons *buttons)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data()->mlx, data()->win, &x, &y);
	// printf("move start x: %d\n", x); //remove
	if (x < data()->mouse_x)
	{
		buttons->mouse_left = true;
		// printf("turn left\n"); //remove
	}
	else if (x > data()->mouse_x)
	{
		buttons->mouse_right = true;
		// printf("turn right\n"); //remove
	}
	if (x < 0 || x > data()->window.width)
	{
		mlx_mouse_move(data()->mlx, data()->win, data()->window.width / 2, data()->window.height / 2);
		mlx_mouse_get_pos(data()->mlx, data()->win, &x, &y);
		// data()->mouse_x = data()->window.width / 2;
	}
	data()->mouse_x = x;
	// printf("move end x: %d\n", data()->mouse_x); //remove
}

int	frame_loop(t_keys *keys)
{
	t_buttons buttons;

	buttons.mouse_left = false;
	buttons.mouse_right = false;
	static_get_mouse_info(&buttons);
	player_update_position(keys, &buttons);
	rays_create();
	walls_draw_to_image();
	if (MINIMAP)
		minimap_draw_to_image();
	window_set_up();
	// int w;
	// int h;
	// mlx_put_image_to_window(data()->mlx, data()->win, mlx_xpm_file_to_image(data()->mlx, "./textures/dirt2048x2048.xpm", &w, &h), 0, 0);
	// mlx_put_image_to_window(data()->mlx, data()->win, mlx_png_file_to_image(data()->mlx, "./textures/dirt2048x2048.png", &w, &h), 0, 0);
	return (EXIT_SUCCESS);
}
