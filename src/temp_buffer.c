/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:36 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:34:18 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	temp_buffer_init(t_temp_buffer *temp)
{
	ft_bzero(temp->buffer, BUFFER_SIZE_CUB3D);
	temp->read_head = 0;
	temp->write_head = 0;
}
