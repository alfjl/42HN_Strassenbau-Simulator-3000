/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:07:37 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:23:21 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_init(t_color *color);
void	textures_init(t_textures *textures);
void	config_file_init(t_config_file	*config);
void	map_init(t_map *map);
void	player_init(t_player *player);

void	data_init(void)
{
	t_config_file	*config_file;
	t_map			*map;
	t_player		*player;

	config_file = &data()->config_file;
	map = &data()->map;
	player = &data()->player;
	// ---------------------------- config_file ------------------------------
	config_file_init(config_file);
	// ---------------------------- map --------------------------------------
	map_init(map);
	// ---------------------------- other stuff ------------------------------
	data()->mlx = NULL;
	data()->win = NULL;
	//char			**map_old;
	//struct s_frame	grid;
	//void			*mlx;
	//void			*win;
	//struct s_frame	minimap;
	//struct s_frame	window;
	//t_img			imgs[IMAGES];
	//int				img_size;
	// ---------------------------- player data ------------------------------
	player_init(player);
	// ---------------------------- other stuff 2 ----------------------------
	//struct s_ray	rays[NUMBER_OF_RAYS];
	// struct s_enemy	enemys;
}
