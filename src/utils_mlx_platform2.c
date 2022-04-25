#include "cub3d.h"

#if defined(__linux__)

int	my_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	return (mlx_mouse_hide(mlx_ptr, win_ptr));
}

int	my_mouse_show(void *mlx_ptr, void *win_ptr)
{
	return (mlx_mouse_show(mlx_ptr, win_ptr));
}
#else

int	my_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (mlx_mouse_hide());
}

int	my_mouse_show(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (mlx_mouse_show());
}
#endif