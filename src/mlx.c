#include "cub3d.h"

static int	static_key_release_hook(int keycode, t_keys *keys)
{
	if (keycode == W_KEY)
		keys->forwards = false;
	else if (keycode == S_KEY)
		keys->backwards = false;
	else if (keycode == A_KEY)
		keys->leftwards = false;
	else if (keycode == D_KEY)
		keys->rightwards = false;
	else if (keycode == LEFT_KEY)
		keys->turnleft = false;
	else if (keycode == RIGHT_KEY)
		keys->turnright = false;
	return (EXIT_SUCCESS);
}

static int	static_key_press_hook(int keycode, t_keys *keys)
{
	if (keycode == ESC_KEY)
		exit_program(SUCCESS);
	if (keycode == W_KEY)
		keys->forwards = true;
	else if (keycode == S_KEY)
		keys->backwards = true;
	else if (keycode == A_KEY)
		keys->leftwards = true;
	else if (keycode == D_KEY)
		keys->rightwards = true;
	else if (keycode == LEFT_KEY)
		keys->turnleft = true;
	else if (keycode == RIGHT_KEY)
		keys->turnright = true;
	return (EXIT_SUCCESS);
}

void	mlx(void)
{
	t_keys	keys;
	void	*mlx;
	void	*win;
	t_frame	*window;

	mlx = data()->mlx;
	window = &data()->window;
	keys.forwards = false;
	keys.backwards = false;
	keys.leftwards = false;
	keys.rightwards = false;
	keys.turnleft = false;
	keys.turnright = false;
	win = mlx_new_window(mlx, window->width, window->height, "cub3D");
	data()->win = win;
	if (data()->win == NULL)
		exit_program(MLX_WIN);
	mlx_hook(data()->win, DestroyNotify,
		StructureNotifyMask, exit_program, NULL); //why isn't this a problem? (NULL)
	mlx_hook(data()->win, KeyPress, KeyPressMask, static_key_press_hook, &keys);
	mlx_hook(data()->win, KeyRelease, KeyReleaseMask, static_key_release_hook,
		&keys);
	mlx_loop_hook(data()->mlx, game, &keys);
	mlx_loop(data()->mlx);
}
