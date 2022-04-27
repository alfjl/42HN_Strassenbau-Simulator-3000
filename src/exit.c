#include "cub3d.h"
#include <errno.h>

static void	static_exit_destroy_images(void *mlx)
{
	t_img	*imgs;
	int		i;

	imgs = data()->imgs;
	i = 0;
	while (i < IMAGES)
	{
		if (imgs[i].ptr != NULL)
			my_destroy_image(mlx, &imgs[i]);
		i++;
	}
}

static void	static_exit_destroy_sprites(void *mlx)
{
	int			i;
	int			nbr;
	t_sprite	*sprite;

	nbr = 0;
	i = 0;
	while (nbr < SPRITENBR)
	{
		sprite = &data()->sprites[nbr];
		while (i <= sprite->count)
		{
			if (sprite->sequence[i].ptr != NULL)
				my_destroy_image(mlx, &sprite->sequence[i]);
			i++;
		}
		nbr++;
	}
}

static char	*static_exit_get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[MLX] = "Mlx init failed!";
	errormessage[MLX_WIN] = "Mlx new window failed!";
	errormessage[MLX_IMAGE] = "Mlx new image failed!";
	return (errormessage[errorcode]);
}

static void	static_exit_free_all(void)
{
	void	*mlx;
	void	*win;
	
	mlx = data()->mlx;
	if (mlx == NULL)
		return ;
	static_exit_destroy_images(mlx);
	static_exit_destroy_sprites(mlx);
	win = data()->win;
	if (win != NULL)
		mlx_destroy_window(mlx, win);
	return ;
}

int	exit_end_program_success(void)
{	
	static_exit_free_all();
	exit(EXIT_SUCCESS);
}

int	exit_end_program_error(int errorcode)
{	
	static_exit_free_all();
	if (errorcode == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (errorcode == SYSTEM)
		ft_printf_stderr("Error\n%s\n", strerror(errno));
	else
		ft_printf_stderr("Error\n%s\n", static_exit_get_error_message(errorcode));
	exit(EXIT_FAILURE);
}
