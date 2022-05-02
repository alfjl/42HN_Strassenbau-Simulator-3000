#include "cub3d.h"

static int	static_mouse_click_hook(int button, int x, int y)
{
	(void)x;
	(void)y;
	if (DOORS_ENABLED && button == LEFT_BUTTON)
	{
		data()->player.status = HITTING;
		doors_open_door();
	}
	if (DOORS_ENABLED && button == RIGHT_BUTTON)
	{
		data()->player.status = HITTING;
		doors_close_door();
	}
	return (EXIT_SUCCESS);
}

static int	static_mouse_move_hook(int x, int y, t_controls *controls)
{
	static int	old_x = WINDOW_WIDTH / 2;
	float		factor;
	int			delta;

	(void)y;
	if (x < old_x)
		controls->mouse_left = true;
	else if (x > old_x)
		controls->mouse_right = true;
	delta = my_abs(x, old_x);
	factor = MOUSE_TURN_FACTOR;
	if (delta > MOUSE_ACCELERATION_KICK_IN)
		factor *= MOUSE_ACCELERATION_FACTOR * delta
			/ MOUSE_ACCELERATION_KICK_IN;
	data()->player.turn_speed = TURN_STEP * factor;
	if (x < 0 || x > data()->window.width)
	{
		my_mouse_move(data()->mlx, data()->win, data()->window.width / 2,
			data()->window.height / 2);
		x = data()->window.width / 2;
	}
	old_x = x;
	return (EXIT_SUCCESS);
}

void	controls_mouse(t_controls *controls)
{
	t_data	*datas;

	datas = data();
	my_mouse_move(datas->mlx, datas->win, datas->window.width / 2,
		datas->window.height / 2);
	mlx_mouse_hook(datas->win, static_mouse_click_hook, NULL);
	mlx_hook(datas->win, MotionNotify, PointerMotionMask,
		static_mouse_move_hook, controls);
}
