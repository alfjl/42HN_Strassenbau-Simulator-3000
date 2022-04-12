# include "cub3d.h"

static int	static_key_release_hook(int keycode, t_keys *keys)
{
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		// ft_printf("W released\n"); //remove
		// key.forwards = 1;
		keys->forwards = false;

	}
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		// ft_printf("A released\n"); //remove
		keys->turnleft = false;
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		// ft_printf("S released\n"); //remove
		keys->turnright = false;
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		// ft_printf("D released\n"); //remove
		keys->backwards = false;
	}
	return (EXIT_SUCCESS);
}

static int	static_key_press_hook(int keycode, t_keys *keys)
{
	if (keycode == ESC_KEY)
		exit_program(SUCCESS);
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		// ft_printf("W pressed\n"); //remove
		keys->forwards = true;

	}
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		// ft_printf("A pressed\n"); //remove
		keys->turnleft = true;
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		// ft_printf("S pressed\n"); //remove
		keys->turnright = true;
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		// ft_printf("D pressed\n"); //remove
		keys->backwards = true;
	}
	return (EXIT_SUCCESS);
}

// static int	static_key_hook(int keycode)
// {
// 	if (keycode == ESC_KEY)
// 		exit_program();
// 	else if (keycode == W_KEY || keycode == UP_KEY)
// 	{
// 		ft_printf("W press\n"); //remove
// 		data()->player.x += data()->player.dx;
// 		data()->player.y += data()->player.dy;
// 	}
// 	else if (keycode == A_KEY || keycode == LEFT_KEY)
// 	{
// 		ft_printf("A press\n"); //remove
// 		data()->player.angle -= STEP_A;
// 		if (data()->player.angle < 0)
// 			data()->player.angle += 2 * PI;
// 		data()->player.dx = cos(data()->player.angle) * STEP;
// 		data()->player.dy = sin(data()->player.angle) * STEP;
// 	}
// 	else if (keycode == S_KEY || keycode == DOWN_KEY)
// 	{
// 		ft_printf("S press\n"); //remove
// 		data()->player.x -= data()->player.dx;
// 		data()->player.y -= data()->player.dy;
// 	}
// 	else if (keycode == D_KEY || keycode == RIGHT_KEY)
// 	{
// 		ft_printf("D press\n"); //remove
// 		data()->player.angle += STEP_A;
// 		if (data()->player.angle > 2 * PI)
// 			data()->player.angle -= 2 * PI;
// 		data()->player.dx = cos(data()->player.angle) * STEP;
// 		data()->player.dy = sin(data()->player.angle) * STEP;
// 	}
// 	// minimap();
// 	return (EXIT_SUCCESS);
// }

void	mlx(void)
{
	t_keys keys;

	keys.backwards = false;
	keys.forwards = false;
	keys.turnleft = false;
	keys.turnright = false;
	
	data()->win = mlx_new_window(data()->mlx, data()->window.width,
		data()->window.height, "cub3D");
	mlx_hook(data()->win, DestroyNotify,
		StructureNotifyMask, exit_program, NULL);
	mlx_hook(data()->win, KeyPress, KeyPressMask, static_key_press_hook, &keys);
	mlx_hook(data()->win, KeyRelease, KeyReleaseMask, static_key_release_hook, &keys);
	mlx_loop_hook(data()->mlx, game, &keys);
	mlx_loop(data()->mlx);
}
