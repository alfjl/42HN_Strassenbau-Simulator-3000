# include "cub3d.h"

static int	static_key_hook(int keycode)
{
	if (keycode == ESC_KEY)
		exit_program();
	else if (keycode == W_KEY || keycode == UP_KEY)
		ft_printf("W\n");
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		ft_printf("A\n");
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		ft_printf("S\n");
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		ft_printf("D\n");
	}
	return (EXIT_SUCCESS);
}

void	mlx(void)
{
	data()->win = mlx_new_window(data()->mlx, data()->window.width,
			data()->window.height, "cub3d");
	// mlx_do_key_autorepeaton(data()->mlx);
	minimap();
	mlx_hook(data()->win, DestroyNotify,
		StructureNotifyMask, exit_program, NULL);
	mlx_hook(data()->win, KeyPress, KeyPressMask, static_key_hook, NULL);
	mlx_loop(data()->mlx);
}
