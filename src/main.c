# include "cub3d.h"

static void	static_init_image_pointers(void)
{
	t_img	*imgs;
	int		i;

	imgs = data()->imgs;
	i = 0;
	while (i < IMAGES)
	{
		imgs[i].ptr = NULL;
		i++;
	}
}

static void	static_initialize_data(void)
{
	data()->win = NULL;
	data()->map.ceiling.rgb = CYAN;
	data()->map.floor.rgb = BLACK;
	data()->map.textures.south = "./textures/stone.xpm";
	data()->map.textures.north = "./textures/moss.xpm";
	data()->map.textures.east = "./textures/magma.xpm";
	data()->map.textures.west = "./textures/bricks.xpm";
	data()->imgs[SOUTH_IMG].path = data()->map.textures.south;
	data()->imgs[NORTH_IMG].path = data()->map.textures.north;
	data()->imgs[EAST_IMG].path = data()->map.textures.east;
	data()->imgs[WEST_IMG].path = data()->map.textures.west;
	data()->minimap.width = data()->map.width * GRID_SIZE;
	data()->minimap.height = data()->map.height * GRID_SIZE;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->line_w = data()->window.width / (NUMBER_OF_RAYS - 1);
	data()->player.x = 1.5;
	data()->player.y = 1.5;
	data()->player.angle = PI / 2;
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
	data()->fps.first = true;
	data()->time = 0; //remove
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
	if (data()->mlx == NULL)
		exit_program(MLX);
	static_init_image_pointers();
	images_create();
	textures_load();
	mlx();
	return(EXIT_SUCCESS);
}