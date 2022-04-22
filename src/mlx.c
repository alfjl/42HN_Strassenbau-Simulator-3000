#include "cub3d.h"

static int	static_key_release_hook(int keycode, t_keys *keys)
{
	if (keycode == W_KEY)
		keys->forwards = false;
	if (keycode == S_KEY)
		keys->backwards = false;
	if (keycode == A_KEY)
		keys->leftwards = false;
	if (keycode == D_KEY)
		keys->rightwards = false;
	if (keycode == LEFT_KEY)
		keys->turnleft = false;
	if (keycode == RIGHT_KEY)
		keys->turnright = false;
	return (EXIT_SUCCESS);
}

static int	static_key_press_hook(int keycode, t_keys *keys)
{
	if (keycode == ESC_KEY)
		exit_program(SUCCESS);
	if (keycode == W_KEY)
		keys->forwards = true;
	if (keycode == S_KEY)
		keys->backwards = true;
	if (keycode == A_KEY)
		keys->leftwards = true;
	if (keycode == D_KEY)
		keys->rightwards = true;
	if (keycode == LEFT_KEY)
		keys->turnleft = true;
	if (keycode == RIGHT_KEY)
		keys->turnright = true;
	if (DOORS && keycode == E_KEY)
		wall_open_door();
	return (EXIT_SUCCESS);
}

static int	static_mouse_click_hook(int button, int x, int y)
{
	printf("click button: %d, x: %d, y: %d\n",button, x, y);
	return (EXIT_SUCCESS);
}

static int	static_mouse_move_hook(int x, int y)
{
	printf("move x: %d, y: %d\n", x, y);
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
	if (win == NULL)
		exit_program(MLX_WIN);
	data()->win = win;
	mlx_hook(win, DestroyNotify,
		StructureNotifyMask, exit_program_success, NULL);
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(win, KeyPress, KeyPressMask, static_key_press_hook, &keys);
	mlx_hook(win, KeyRelease, KeyReleaseMask, static_key_release_hook,
		&keys);
	mlx_mouse_hook(win, static_mouse_click_hook, NULL);
	mlx_hook(win, MotionNotify, PointerMotionMask, static_mouse_move_hook, NULL);
	mlx_loop_hook(mlx, frame_loop, &keys);
	mlx_loop(mlx);
}
