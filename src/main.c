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
	data()->imgs[FLOOR_IMG].path = TEXTURE_FLOOR;
	data()->imgs[CEILING_IMG].path = TEXTURE_CEILING;
	data()->imgs[SKY_IMG].path = TEXTURE_SKY;
	data()->minimap.width = data()->map.width * MAP_GRID_SIZE;
	data()->minimap.height = data()->map.height * MAP_GRID_SIZE;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->line_w = data()->window.width / (NUMBER_OF_RAYS - 1);
}

// static void	static_get_map_file_data(void)
// {
// 	///////map
// 	data()->map.grid = data()->map_old; //workaround to get map into new struct
// 	data()->map.height = data()->map.height; //placeholder
// 	data()->map.width = data()->map.width; //placeholder
// 	//colors
// 	data()->map.ceiling.rgb = 0x00088FF; //placeholder
// 	data()->map.floor.rgb = BROWN; //placeholder
// 	//textures
// 	// data()->map.textures.south = "./textures/stone.xpm";
// 	// data()->map.textures.north = "./textures/moss.xpm";
// 	// data()->map.textures.east = "./textures/magma.xpm";
// 	data()->map.textures.north = TEXTURE_NORTH; //placeholder
// 	data()->map.textures.south = TEXTURE_SOUTH; //placeholder
// 	data()->map.textures.east = TEXTURE_EAST; //placeholder
// 	data()->map.textures.west = TEXTURE_WEST; //placeholder
// 	///////player
// 	data()->player.status = IDLE;
// 	data()->player.step_size = MOVE_STEP;
// 	data()->player.turn_speed = TURN_STEP;
// 	data()->player.x = 1.5; //placeholder
// 	data()->player.y = 1.5; //placeholder
// 	data()->player.dz = 0;
// 	data()->player.is_jumping = false;
// 	data()->player.is_crouching = false;
// 	data()->player.angle = M_PI / 2; //placeholder
// 	calculate_pos_delta();
// }

int	main(int argc, char *argv[])
{
	t_config_file	*config;
	t_map			*map;

	data_init();
	static_images_initialize();
	static_sprites_initialize();
	if (argc != 2)
		exit_end_program_error(ARGUMENT_NR);
	if (validation_typecheck_cub(argv[1]) == false)
		exit_end_program_error(WRONG_FILETYPE);
	config = &data()->config_file;
	map = &data()->map;
	config->buffer = read_fd(argv[1]);
	if (config->buffer == NULL)
		exit_end_program_error(PROBLEM_READING_CONFIG);
	config_parse(config, map);
	// TPO --------------------------------------------------------------------
	printf("############## BEGINNING of parsing test ################\n");
	// unsigned int i = 0;
	// while (i < map->height)
	// {
	// 	unsigned int j = 0;
	// 	while (j < map->width - 1)
	// 	{
	// 		write(1, &map->grid[i][j], 1);
	// 		j++;
	// 	}
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	//printf("ceiling rgb = %d\n", map->ceiling.rgb);
	//printf("floor rgb = %d\n", map->floor.rgb);
	//printf("ceiling rgb = %X\n", map->ceiling.rgb);
	//printf("floor rgb = %X\n", map->floor.rgb);
	printf("map height = %d\n", map->height);
	printf("map width = %d\n", map->width);
	//printf("errorcode = %d\n", config->errorcode);
	printf("############## END of parsing test ###################\n");
	// TPO -------------------------------------------------------------------
	if (config->errorcode != 0)
		exit_end_program_error(config->errorcode);
	data()->mlx = mlx_init();
	if (data()->mlx == NULL)
		exit_end_program_error(MLX);
	static_data_struct_initialize();
	images_create();
	textures_load();
	if (SPRITES_ENABLED)
		sprites_load();
	mlx();
	free_all();
	return (0);
}
