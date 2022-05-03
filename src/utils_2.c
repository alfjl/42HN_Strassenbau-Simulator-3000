/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:09:16 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 19:09:33 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cb;
	size_t			i;

	cb = b;
	i = 0;
	while (i < len)
	{
		cb[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
char	*read_fd(char *path)
{
	int				fd;
	t_stringbuilder	builder;
	t_temp_buffer	temp;
	int	i;

	fd = open(path, O_RDONLY);
	stringbuilder_init(&builder);
	if (builder.buffer == NULL || fd < 0)
	{
		close(fd);
		return (NULL);
	}
	temp_buffer_init(&temp);
	temp.write_head = read(fd, &temp.buffer, sizeof(temp.buffer));
	i = 0;
	while (temp.write_head > 0)
	{
		temp.read_head = 0;
		while (temp.read_head < temp.write_head)
		{
			if (stringbuilder_append_char(&builder, temp.buffer[temp.read_head]) == false)
				printf("here\n") ; //remove
			temp.read_head++;
		}
		temp.write_head = read(fd, &temp.buffer, sizeof(temp.buffer));
		i++;
		// printf("head:%d i: %d\n", temp.write_head, i);
	}
	close(fd);
	return (stringbuilder_trim_and_return_buffer(&builder));
}
