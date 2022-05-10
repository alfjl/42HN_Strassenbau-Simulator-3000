/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:18 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:54:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_sky_color(t_ray *ray, int y)
{
	int	tx;
	int	ty;

	if (!SKY_ENABLED)
		return (data()->map.ceiling.rgb);
	tx = ray->angle * (data()->imgs[SKY_IMG].width / (2 * M_PI));
	ty = y + data()->imgs[SKY_IMG].height / 4 - data()->player.dz;
	return (get_pixel_color(&data()->imgs[SKY_IMG], tx, ty));
}
