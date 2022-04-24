#include "cub3d.h"

static int	static_sprites_determine_color(t_img *img, int x, int y)
{
	int		color;
	float	scale_x;
	float	scale_y;
	float	tx;
	float	ty;

	scale_x = img->width / (float)SPRITE_SIZE;
	scale_y = img->height / (float)SPRITE_SIZE;
	tx = x * scale_x;
	ty = y * scale_y;
	color = *(unsigned int *)(img->addr
			+ (unsigned int)((int)ty * img->line_len
				+ (int)tx * (img->bits_per_pixel / 8)));
	return (color);
}

static void	static_resize_img(t_img *tmp, t_img *img)
{
	int		y;
	int		x;
	int		color;

	img->ptr = my_new_image(data()->mlx, SPRITE_SIZE,
			SPRITE_SIZE, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = static_sprites_determine_color(tmp, x, y);
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

static void	static_create_img_from_sprite(int spritenbr)
{
	t_img		*tmp;
	t_img		*img;
	t_sprite	*sprite;
	int		i;

	tmp = &data()->imgs[TMP_IMG];
	sprite = &data()->sprites[spritenbr];
	i = 0;
	while (i < sprite->count)
	{
		img = &sprite->sequence[i];
		tmp->ptr = mlx_xpm_file_to_image(data()->mlx, img->path,
				&tmp->width, &tmp->height);
		if (tmp->ptr == NULL)
			exit_program(MLX_IMAGE);
		tmp->addr = mlx_get_data_addr(tmp->ptr, &tmp->bits_per_pixel,
				&tmp->line_len, &tmp->endian);
		static_resize_img(tmp, img);
		my_destroy_image(data()->mlx, tmp);
		i++;
	}
}

void	sprites_load(void)
{
	data()->sprites[SHOVEL_SPRITE].sequence[0].path = "./sprites/shovel10.xpm";
	data()->sprites[SHOVEL_SPRITE].count = 1;
	data()->sprites[SHOVEL_SPRITE].counter = 0;
	data()->sprites[SHOVEL_SPRITE].enabled = true;
	data()->sprites[SHOVEL_SPRITE].sign = 1;
	data()->sprites[SHOVEL_SPRITE].speed = 1;
	static_create_img_from_sprite(SHOVEL_SPRITE);

	data()->sprites[SHOVEL_WALK_SPRITE].sequence[0].path = "./sprites/shovel0.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].sequence[1].path = "./sprites/shovel1.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].sequence[2].path = "./sprites/shovel2.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].sequence[3].path = "./sprites/shovel3.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].sequence[4].path = "./sprites/shovel4.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].sequence[5].path = "./sprites/shovel5.xpm";
	data()->sprites[SHOVEL_WALK_SPRITE].count = SPRITE_COUNT;
	data()->sprites[SHOVEL_WALK_SPRITE].counter = 0;
	data()->sprites[SHOVEL_WALK_SPRITE].enabled = false;
	data()->sprites[SHOVEL_WALK_SPRITE].sign = 1;
	data()->sprites[SHOVEL_WALK_SPRITE].speed = 3;
	static_create_img_from_sprite(SHOVEL_WALK_SPRITE);

	data()->sprites[SHOVEL_HIT_SPRITE].sequence[0].path = "./sprites/shovel_hit0.xpm";
	data()->sprites[SHOVEL_HIT_SPRITE].sequence[1].path = "./sprites/shovel_hit0.xpm";
	data()->sprites[SHOVEL_HIT_SPRITE].count = 2;
	data()->sprites[SHOVEL_HIT_SPRITE].counter = 0;
	data()->sprites[SHOVEL_HIT_SPRITE].enabled = false;
	data()->sprites[SHOVEL_HIT_SPRITE].sign = 1;
	data()->sprites[SHOVEL_HIT_SPRITE].speed = 6;
	static_create_img_from_sprite(SHOVEL_HIT_SPRITE);
}
