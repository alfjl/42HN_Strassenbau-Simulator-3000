/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:53:43 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:53:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	debug_print(void)
{
	t_map			*map;
	unsigned int	i;
	unsigned int	j;

	map = &data()->map;
	printf("############## BEGINNING of test print ################\n");
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			write(1, "|", 1);
			write(1, &map->grid[i][j], 1);
			write(1, "|", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	printf("c rgb = %X, f rgb = %X\n", map->ceiling.rgb, map->floor.rgb);
	printf("map height = %d, map->width = %d\n", map->height, map->width);
	printf("############## END of test print ###################\n");
}

/* ----------------------------- FUNC 2 ------------------------------------ */
int	main(int argc, char *argv[])
{
	t_config_file	*config;
	t_map			*map;

	data_init();
	if (argc != 2)
		exit_end_program_error(ARGUMENT_NR);
	if (validation_typecheck_cub(argv[1]) == false)
		exit_end_program_error(WRONG_FILETYPE);
	config = &data()->config_file;
	map = &data()->map;
	config->buffer = read_fd(argv[1]);
	if (config->buffer == NULL)
		exit_end_program_error(PROBLEM_READING_CONFIG);
	config_parse(config, map);
	if (config->errorcode != 0)
		exit_end_program_error(config->errorcode);
	if (DEBUG == 1)
		debug_print();
	mlx_start();
	free_all();
	return (0);
}
