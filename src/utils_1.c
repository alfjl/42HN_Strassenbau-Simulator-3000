/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:09:10 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/29 10:09:11 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
unsigned long long	ft_atoull(const char *str)
{
	unsigned long long	result;
	unsigned int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) != false)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}
