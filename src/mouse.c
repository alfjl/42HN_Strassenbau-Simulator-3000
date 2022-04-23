#include "cub3d.h"

// int		my_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
// {

// 	if (LINUX)
// 		mlx_mouse_move(mlx_ptr, win_ptr, x, y);
// 	else
// 	{
// 		(void)mlx_ptr;
// 		mlx_mouse_move(win_ptr, x, y);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int		my_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
// {
// 	if (LINUX)
// 		mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
// 	else
// 	{
// 		(void)mlx_ptr;
// 		mlx_mouse_get_pos(win_ptr, x, y);
// 	}
// }

static int	static_mouse_click_hook(int button, int x, int y)
{
	printf("mouse click\tx: %d, y: %d, button: %d\n", x, y, button);
	return (EXIT_SUCCESS);
}

static int	static_mouse_move_hook(int x, int y, t_controls *controls)
{
	static int	old_x;

	if (x < old_x)
	{
		controls->mouse_left = true;
		// printf("turn left\n"); //remove
	}
	else if (x > old_x)
	{
		controls->mouse_right = true;
		// printf("turn right\n"); //remove
	}
	if (x < 0 || x > data()->window.width)
	{
		mlx_mouse_move(data()->mlx, data()->win, data()->window.width / 2,
			data()->window.height / 2);
		// mlx_mouse_get_pos(data()->mlx, data()->win, &x, &y);
		x = data()->window.width / 2;
	}
	old_x = x;
	// printf("move end x: %d\n", old_x); //remove
	printf("mouse move\tx: %d, y: %d\n", x, y); //remove
	return (EXIT_SUCCESS);
}

void	mouse(t_controls *controls)
{
	t_data	*datas;

	datas = data();
	mlx_mouse_move(datas->mlx, datas->win, datas->window.width / 2,
		datas->window.height / 2);
	mlx_mouse_hook(datas->win, static_mouse_click_hook, NULL);
	mlx_hook(datas->win, MotionNotify, PointerMotionMask,
		static_mouse_move_hook, controls);
}
