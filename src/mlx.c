#include "cub3d.h"

static int	static_key_release_hook(int keycode, t_controls *controls)
{
	if (keycode == W_KEY)
		controls->forwards = false;
	if (keycode == S_KEY)
		controls->backwards = false;
	if (keycode == A_KEY)
		controls->leftwards = false;
	if (keycode == D_KEY)
		controls->rightwards = false;
	if (keycode == LEFT_KEY)
		controls->turnleft = false;
	if (keycode == RIGHT_KEY)
		controls->turnright = false;
	return (EXIT_SUCCESS);
}

static int	static_key_press_hook(int keycode, t_controls *controls)
{
	if (keycode == ESC_KEY)
		exit_program(SUCCESS);
	if (keycode == W_KEY)
		controls->forwards = true;
	if (keycode == S_KEY)
		controls->backwards = true;
	if (keycode == A_KEY)
		controls->leftwards = true;
	if (keycode == D_KEY)
		controls->rightwards = true;
	if (keycode == LEFT_KEY)
		controls->turnleft = true;
	if (keycode == RIGHT_KEY)
		controls->turnright = true;
	if (DOORS && keycode == E_KEY)
		wall_open_door();
	return (EXIT_SUCCESS);
}

void	mlx(void)
{
	static t_controls	controls;
	void				*mlx;
	void				*win;
	t_frame				*window;

	mlx = data()->mlx;
	window = &data()->window;
	win = mlx_new_window(mlx, window->width, window->height, "cub3D");
	if (win == NULL)
		exit_program(MLX_WIN);
	data()->win = win;
	mlx_hook(win, DestroyNotify,
		StructureNotifyMask, exit_program_success, NULL);
	mlx_do_key_autorepeatoff(mlx);
	mlx_mouse_hide(mlx, win);
	mlx_hook(win, KeyPress, KeyPressMask, static_key_press_hook, &controls);
	mlx_hook(win, KeyRelease, KeyReleaseMask, static_key_release_hook,
		&controls);
	if (MOUSE)
		mouse(&controls);
	mlx_loop_hook(mlx, frame_loop, &controls);
	mlx_loop(mlx);
}
