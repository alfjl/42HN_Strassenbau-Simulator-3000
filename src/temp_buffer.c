/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:36 by alanghan          #+#    #+#             */
/*   Updated: 2022/05/10 11:49:53 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	temp_buffer_init(t_temp_buffer *temp)
{
	ft_bzero(temp->buffer, BUFFER_SIZE_BUILDER);
	temp->read_head = 0;
	temp->write_head = 0;
}
