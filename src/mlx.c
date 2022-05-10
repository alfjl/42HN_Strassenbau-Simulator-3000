#include "cub3d.h"

static void	static_mlx_create_images(void *mlx)
{
	images_create(mlx);
	textures_convert_to_image(mlx);
	if (SPRITES_ENABLED)
		sprites_convert_to_image(mlx);
}

static void	*static_mlx_open_window(void *mlx)
{
	void	*win;
	t_frame	*window;

	window = &data()->window;
	win = mlx_new_window(mlx, window->width, window->height, "cub3D");
	if (win == NULL)
		exit_end_program_error(MLX_WIN);
	return (win);
}

static void	static_mlx_setup_hooks(void *mlx, void *win)
{
	static t_controls	controls;

	mlx_hook(win, DestroyNotify,
		StructureNotifyMask, exit_end_program_success, NULL);
	mlx_do_key_autorepeatoff(mlx);
	if (BONUS)
		my_mouse_hide(mlx, win);
	controls_keyboard(&controls);
	if (MOUSE_ENABLED)
		controls_mouse(&controls);
	mlx_loop_hook(mlx, frame, &controls);
}

void	mlx_start(void)
{
	void				*mlx;
	void				*win;

	mlx = mlx_init();
	if (mlx == NULL)
		exit_end_program_error(MLX);
	data()->mlx = mlx;
	win = static_mlx_open_window(mlx);
	data()->win = win;
	static_mlx_create_images(mlx);
	static_mlx_setup_hooks(mlx, win);
	mlx_loop(mlx);
}
