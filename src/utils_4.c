/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:39 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:54:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	pythagoras_hypotenuse(double a, double b)
{
	return (sqrt(a * a + b * b));
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}
