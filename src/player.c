/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:00 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:30:50 by alanghan         ###   ########.fr       */
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
