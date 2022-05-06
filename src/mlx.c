#include "cub3d.h"

void	mlx(void)
{
	static t_controls	controls;
	void				*mlx;
	void				*win;
	t_frame				*window;

	data()->mlx = mlx_init();
	if (data()->mlx == NULL)
		exit_end_program_error(MLX);
	images_create();
	textures_load();
	if (SPRITES_ENABLED)
		sprites_load();
	mlx = data()->mlx;
	window = &data()->window;
	win = mlx_new_window(mlx, window->width, window->height, "cub3D");
	if (win == NULL)
		exit_end_program_error(MLX_WIN);
	data()->win = win;
	mlx_hook(win, DestroyNotify,
		StructureNotifyMask, exit_end_program_success, NULL);
	mlx_do_key_autorepeatoff(mlx);
	my_mouse_hide(mlx, win);
	controls_keyboard(&controls);
	if (MOUSE_ENABLED)
		controls_mouse(&controls);
	mlx_loop_hook(mlx, frame, &controls);
	mlx_loop(mlx);
}
