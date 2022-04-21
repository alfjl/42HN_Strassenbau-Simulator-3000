#include "cub3d.h"
#include <errno.h>

static void	static_mlx_destroy(void)
{
	void	*mlx;
	t_img	*imgs;
	int		i;

	mlx = data()->mlx;
	imgs = data()->imgs;
	i = 0;
	while (i < IMAGES)
	{
		if (imgs[i].ptr != NULL)
			my_destroy_image(mlx, (t_img *)&imgs[i].ptr);
		i++;
	}
	if (data()->win != NULL)
		mlx_destroy_window(data()->mlx, data()->win);
}

static char	*static_get_error_message(int errorcode)
{
	char	*errormessage[ERRORS];

	errormessage[MLX] = "Mlx init failed!";
	errormessage[MLX_WIN] = "Mlx new window failed!";
	errormessage[MLX_IMAGE] = "Mlx new image failed!";
	return (errormessage[errorcode]);
}

static void	static_free_all(void)
{
	static_mlx_destroy();
	return ;
}

int	exit_program_success(void)
{	
	static_free_all();
	exit(EXIT_SUCCESS);
}

int	exit_program(int errorcode)
{	
	static_free_all();
	if (errorcode == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (errorcode == SYSTEM)
		ft_printf_stderr("Error\n%s\n", strerror(errno));
	else
		ft_printf_stderr("Error\n%s\n", static_get_error_message(errorcode));
	exit(EXIT_FAILURE);
}
