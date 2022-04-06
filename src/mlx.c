# include "cub3d.h"

static int	static_key_hook(int keycode)
{
	if (keycode == ESC_KEY)
		exit_program();
	else if (keycode == W_KEY || keycode == UP_KEY)
	{
		ft_printf("W\n"); //remove
		data()->player.x += data()->player.dx;
		data()->player.y += data()->player.dy;
	}
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		ft_printf("A\n"); //remove
		data()->player.angle -= STEP_A;
		if (data()->player.angle < 0)
			data()->player.angle += 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		ft_printf("S\n"); //remove
		data()->player.x -= data()->player.dx;
		data()->player.y -= data()->player.dy;
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		ft_printf("D\n"); //remove
		data()->player.angle += STEP_A;
		if (data()->player.angle > 2 * PI)
			data()->player.angle -= 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
	// minimap();
	return (EXIT_SUCCESS);
}

void	mlx(void)
{
	data()->win = mlx_new_window(data()->mlx, data()->window.width,
			data()->window.height, "cub3d");
	mlx_do_key_autorepeaton(data()->mlx);
	// minimap();
	mlx_hook(data()->win, DestroyNotify,
		StructureNotifyMask, exit_program, NULL);
	mlx_hook(data()->win, KeyPress, KeyPressMask, static_key_hook, NULL);
	mlx_loop_hook(data()->mlx, minimap, NULL);
	mlx_loop(data()->mlx);
}
