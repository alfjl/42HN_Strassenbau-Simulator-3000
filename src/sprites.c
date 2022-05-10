/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:21 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:54:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_create_img_from_sprite(void *mlx, int spritenbr)
{
	t_img		*tmp;
	t_img		*img;
	t_sprite	*sprite;
	int			i;

	tmp = &data()->imgs[TMP_IMG];
	sprite = &data()->sprites[spritenbr];
	i = 0;
	while (i < sprite->count)
	{
		img = &sprite->sequence[i];
		tmp->ptr = my_xpm_file_to_image(mlx, img->path, tmp);
		if (tmp->ptr == NULL)
			exit_end_program_error(MLX_IMAGE);
		textures_resize_img(mlx, tmp, img, SPRITE_SIZE);
		my_destroy_image(mlx, tmp);
		i++;
	}
}

void	sprites_convert_to_image(void *mlx)
{
	t_sprite	*sprites;

	sprites = data()->sprites;
	sprites[SHOVEL_SPRITE].sequence[0].path = "./sprites/shovel_idle0.xpm";
	sprites[SHOVEL_SPRITE].count = 1;
	static_create_img_from_sprite(mlx, SHOVEL_SPRITE);
	sprites[SHOVEL_WALK_SPRITE].sequence[0].path = "./sprites/shovel0.xpm";
	sprites[SHOVEL_WALK_SPRITE].sequence[1].path = "./sprites/shovel1.xpm";
	sprites[SHOVEL_WALK_SPRITE].sequence[2].path = "./sprites/shovel2.xpm";
	sprites[SHOVEL_WALK_SPRITE].sequence[3].path = "./sprites/shovel3.xpm";
	sprites[SHOVEL_WALK_SPRITE].sequence[4].path = "./sprites/shovel4.xpm";
	sprites[SHOVEL_WALK_SPRITE].sequence[5].path = "./sprites/shovel5.xpm";
	sprites[SHOVEL_WALK_SPRITE].count = MAX_SPRITE_COUNT;
	sprites[SHOVEL_WALK_SPRITE].speed = 3;
	static_create_img_from_sprite(mlx, SHOVEL_WALK_SPRITE);
	sprites[SHOVEL_HIT_SPRITE].sequence[0].path = "./sprites/shovel_hit0.xpm";
	sprites[SHOVEL_HIT_SPRITE].sequence[1].path = "./sprites/shovel_hit0.xpm";
	sprites[SHOVEL_HIT_SPRITE].count = 2;
	sprites[SHOVEL_HIT_SPRITE].speed = 6;
	static_create_img_from_sprite(mlx, SHOVEL_HIT_SPRITE);
}
