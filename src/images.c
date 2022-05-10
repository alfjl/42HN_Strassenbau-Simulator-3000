/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:53:38 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:53:39 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_images_create_environment_img(void *mlx, t_img *img)
{
	img->ptr = my_new_image(mlx, data()->window.width,
			data()->window.height, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
}

static void	static_images_create_player_img(void *mlx, t_img *img)
{
	img->ptr = my_new_image(mlx,
			MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	image_fill(img, MINIMAP_PLAYER_COLOR);
}

static void	static_images_create_minimap_img(void *mlx, t_img *img)
{
	img->ptr = my_new_image(mlx, MINIMAP_RADIUS * 2 * MAP_GRID_SIZE,
			MINIMAP_RADIUS * 2 * MAP_GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
}

void	images_create(void *mlx)
{
	t_img	*imgs;

	imgs = data()->imgs;
	static_images_create_player_img(mlx, &imgs[PLAYER_IMG]);
	static_images_create_environment_img(mlx, &imgs[ENV_IMG]);
	static_images_create_minimap_img(mlx, &imgs[MINIMAP_IMG]);
}
