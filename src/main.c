# include "cub3d.h"

static void	static_initialize_data(void)
{
	data()->minimap.width = data()->grid.width * GRID_SIZE;
	data()->minimap.height = data()->grid.height * GRID_SIZE;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->player.x = 1.5;
	data()->player.y = 1.5;
	data()->player.angle = PI / 2;
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("ERROR\n");
		return (EXIT_FAILURE);
	}
	read_map(argv[1]);
	static_initialize_data();
	data()->mlx = mlx_init();
	create_images();
	mlx();
	return(EXIT_SUCCESS);
}