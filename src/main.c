# include "cub3d.h"

static void	static_initialize_data(void)
{
	data()->map.ceiling.rgb = CYAN;
	data()->map.floor.rgb = BLACK;
	data()->map.textures.south = "./textures/stone.xpm";
	data()->map.textures.north = "./textures/moss.xpm";
	data()->map.textures.east = "./textures/magma.xpm";
	data()->map.textures.west = "./textures/bricks.xpm";
	data()->minimap.width = data()->map.width * GRID_SIZE;
	data()->minimap.height = data()->map.height * GRID_SIZE;
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
	// printf("RED: %u\n", createARGB(255, 0, 0, 255));
	// printf("RED: %u\n", RED);
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