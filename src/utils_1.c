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

// /* ----------------------------- FUNC 1 ------------------------------------ */
// unsigned int	ft_strlen(const char *str)
// {
// 	size_t	length;

// 	length = 0;
// 	while (str[length] != '\0')
// 		length++;
// 	return (length);
// }

// /* ----------------------------- FUNC 2 ------------------------------------ */
// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*cs;
// 	size_t			i;

// 	cs = s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		cs[i] = '\0';
// 		i++;
// 	}
// }

// /* ----------------------------- FUNC 3 ------------------------------------ */
// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*memory;

// 	memory = (void *)malloc(count * size);
// 	if (!memory)
// 		return ((void *) NULL);
// 	ft_bzero(memory, (count * size));
// 	return ((void *)memory);
// }

// /* ----------------------------- FUNC 4 ------------------------------------ */
// bool	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (true);
// 	return (false);
// }

/* ----------------------------- FUNC 5 ------------------------------------ */
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
