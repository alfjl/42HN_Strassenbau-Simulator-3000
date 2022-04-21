#include "cub3d.h"

static void	static_initialize_pointers(void)
{
	t_img	*imgs;
	int		i;

	data()->mlx = NULL;
	data()->win = NULL;
	imgs = data()->imgs;
	i = 0;
	while (i < IMAGES)
	{
		imgs[i].ptr = NULL;
		i++;
	}
}

static void	static_initialize_data_struct(void)
{
	data()->imgs[SOUTH_IMG].path = data()->map.textures.south;
	data()->imgs[NORTH_IMG].path = data()->map.textures.north;
	data()->imgs[EAST_IMG].path = data()->map.textures.east;
	data()->imgs[WEST_IMG].path = data()->map.textures.west;
	data()->minimap.width = data()->map.width * GRID_SIZE;
	data()->minimap.height = data()->map.height * GRID_SIZE;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->line_w = data()->window.width / (NUMBER_OF_RAYS - 1);
	data()->fps.first = true; //remove
	data()->time = 0; //remove
}

static void	static_get_map_file_data(void)
{
	///////map
	data()->map.grid = data()->map_old; //workaround to get map into new struct
	data()->map.height = data()->map.height; //placeholder
	data()->map.width = data()->map.width; //placeholder
	//colors
	data()->map.ceiling.rgb = CYAN; //placeholder
	data()->map.floor.rgb = BLACK; //placeholder
	//textures
	// data()->map.textures.south = "./textures/stone.xpm";
	// data()->map.textures.north = "./textures/moss.xpm";
	// data()->map.textures.east = "./textures/magma.xpm";
	data()->map.textures.south = "./textures/bricks.xpm"; //placeholder
	data()->map.textures.north = "./textures/bricks.xpm"; //placeholder
	data()->map.textures.east = "./textures/bricks.xpm"; //placeholder
	data()->map.textures.west = "./textures/bricks.xpm"; //placeholder
	///////player
	data()->player.x = 1.5; //placeholder
	data()->player.y = 1.5; //placeholder
	data()->player.angle = PI / 2; //placeholder
	calculate_pos_delta();
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char **argv)
{
	static_initialize_pointers();
	if (argc != 2)
	{
		ft_printf("ERROR\n");
		return (EXIT_FAILURE);
	}
	read_map(argv[1]);
	static_get_map_file_data();
	data()->mlx = mlx_init();
	if (data()->mlx == NULL)
		exit_program(MLX);
	static_initialize_data_struct();
	images_create();
	textures_load();
	mlx();
	return (EXIT_SUCCESS);
}
