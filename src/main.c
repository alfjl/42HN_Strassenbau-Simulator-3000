#include "cub3d.h"

static void	static_images_initialize(void)
{
	t_img	*imgs;
	int		i;

	imgs = data()->imgs;
	i = 0;
	while (i < IMG_NBR)
	{
		imgs[i].ptr = NULL;
		imgs[i].width = 0;
		imgs[i].height = 0;
		imgs[i].addr = NULL;
		imgs[i].bits_per_pixel = 0;
		imgs[i].line_len = 0;
		imgs[i].endian = 0;
		imgs[i].path = NULL;
		i++;
	}
}

static void	static_sprites_initialize(void)
{
	int			i;
	int			nbr;
	t_sprite	*sprite;

	nbr = 0;
	i = 0;
	while (nbr < SPRITE_NBR)
	{
		sprite = &data()->sprites[nbr];
		sprite->name = NULL;
		sprite->count = MAX_SPRITE_COUNT;
		sprite->counter = 0;
		sprite->speed = 1;
		sprite->sign = 1;
		while (i <= sprite->count)
		{
			sprite->sequence[i].ptr = NULL;
			i++;
		}
		nbr++;
	}
}

static void	static_data_struct_initialize(void)
{
	data()->imgs[SOUTH_IMG].path = data()->map.textures.south;
	data()->imgs[NORTH_IMG].path = data()->map.textures.north;
	data()->imgs[EAST_IMG].path = data()->map.textures.east;
	data()->imgs[WEST_IMG].path = data()->map.textures.west;
	data()->imgs[FLOOR_IMG].path = "./textures/inca_stone128x128.xpm";
	data()->imgs[CEILING_IMG].path = "./textures/moss.xpm";
	data()->imgs[SKY_IMG].path = "./textures/sky_tiled2048x1024.xpm";
	data()->minimap.width = data()->map.width * MAP_GRID_SIZE;
	data()->minimap.height = data()->map.height * MAP_GRID_SIZE;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->line_w = data()->window.width / (NUMBER_OF_RAYS - 1);
}

static void	static_get_map_file_data(void)
{
	///////map
	data()->map.grid = data()->map_old; //workaround to get map into new struct
	data()->map.height = data()->map.height; //placeholder
	data()->map.width = data()->map.width; //placeholder
	//colors
	data()->map.ceiling.rgb = CYAN; //placeholder
	data()->map.floor.rgb = BROWN; //placeholder
	//textures
	// data()->map.textures.south = "./textures/stone.xpm";
	// data()->map.textures.north = "./textures/moss.xpm";
	// data()->map.textures.east = "./textures/magma.xpm";
	data()->map.textures.west = "./textures/dirt_low2048x2048.xpm"; //placeholder
	data()->map.textures.south = data()->map.textures.west; //placeholder
	data()->map.textures.north = data()->map.textures.west; //placeholder
	data()->map.textures.east = data()->map.textures.west; //placeholder
	///////player
	data()->player.status = IDLE;
	data()->player.step_size = MOVE_STEP;
	data()->player.turn_speed = TURN_STEP;
	data()->player.x = 1.5; //placeholder
	data()->player.y = 1.5; //placeholder
	data()->player.dz = 0;
	data()->player.is_jumping = false;
	data()->player.is_crouching = false;
	data()->player.angle = M_PI / 2; //placeholder
	calculate_pos_delta();
}

int	main(int argc, char **argv)
{
	data()->mlx = NULL;
	data()->win = NULL;
	static_images_initialize();
	static_sprites_initialize();
	if (argc != 2)
	{
		ft_printf("ERROR\n");
		return (EXIT_FAILURE);
	}
	map_read(argv[1]);
	static_get_map_file_data();
	data()->mlx = mlx_init();
	if (data()->mlx == NULL)
		exit_end_program_error(MLX);
	static_data_struct_initialize();
	images_create();
	textures_load();
	if (SPRITES_ENABLED)
		sprites_load();
	mlx();
	return (EXIT_SUCCESS);
}
