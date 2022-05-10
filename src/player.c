/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:00 by alanghan          #+#    #+#             */
/*   Updated: 2022/05/10 11:13:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
float	player_calculate_angle(char direction)
{
	float	angle;

	if (direction == 'N')
		angle = 3 * M_PI_2;
	else if (direction == 'S')
		angle = M_PI_2;
	else if (direction == 'E')
		angle = 0.0;
	else if (direction == 'W')
		angle = M_PI;
	else
		angle = -1.0;
	return (angle);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	player_update_z_position(void)
{
	t_player	*player;

	player = &data()->player;
	if (player->is_jumping && player->dz < 0)
		player->dz = 0;
	else if (player->is_jumping && player->dz < JUMP_DELTA)
		player->dz += GRAVITY;
	else if (player->dz > 0)
	{
		player->is_jumping = false;
		player->dz -= GRAVITY;
		if (player->dz < 0)
			player->dz = 0;
	}
}
