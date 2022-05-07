/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:07:37 by alanghan          #+#    #+#             */
/*   Updated: 2022/05/06 18:25:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_init(t_color *color);
void	textures_init(t_textures *textures);
void	config_file_init(t_config_file	*config);
void	map_init(t_map *map);
void	player_init(t_player *player);

/* ----------------------------- FUNC 1 ------------------------------------ */
static void	static_images_init(void)
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
	data()->imgs[FLOOR_IMG].path = TEXTURE_FLOOR;
	data()->imgs[CEILING_IMG].path = TEXTURE_CEILING;
	data()->imgs[SKY_IMG].path = TEXTURE_SKY;
}

/* ----------------------------- FUNC 2 ------------------------------------ */
static void	static_sprites_init(void)
{
	int			i;
	int			nbr;
	t_sprite	*sprite;

	nbr = 0;
	while (nbr < SPRITE_NBR)
	{
		sprite = &data()->sprites[nbr];
		sprite->name = NULL;
		sprite->count = MAX_SPRITE_COUNT;
		sprite->counter = 0;
		sprite->speed = 1;
		sprite->sign = 1;
		i = 0;
		while (i < sprite->count)
		{
			sprite->sequence[i].ptr = NULL;
			i++;
		}
		nbr++;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	data_init(void)
{
	t_config_file	*config_file;
	t_map			*map;
	t_player		*player;

	config_file = &data()->config_file;
	map = &data()->map;
	player = &data()->player;
	config_file_init(config_file);
	map_init(map);
	data()->mlx = NULL;
	data()->win = NULL;
	data()->window.width = WINDOW_WIDTH;
	data()->window.height = WINDOW_HEIGHT;
	data()->line_w = data()->window.width / (NUMBER_OF_RAYS - 1);
	player_init(player);
	static_images_init();
	static_sprites_init();
}
