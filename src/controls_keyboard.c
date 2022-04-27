#include "cub3d.h"

static int	static_keyboard_key_release_hook(int keycode, t_controls *controls)
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

static int	static_keyboard_key_press_hook(int keycode, t_controls *controls)
{
	if (keycode == ESC_KEY)
		exit_end_program_success();
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
	if (DOORS_ENABLED && keycode == E_KEY)
	{
		data()->player.status = HITTING;
		walls_open_door();
	}
	return (EXIT_SUCCESS);
}

void	keyboard(t_controls *controls)
{
	void	*win;

	win = data()->win;
	mlx_hook(win, KeyPress, KeyPressMask, static_keyboard_key_press_hook,
		controls);
	mlx_hook(win, KeyRelease, KeyReleaseMask, static_keyboard_key_release_hook,
		controls);
}
