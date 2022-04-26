#include "cub3d.h"

static int	static_map_determine_max_y(void)
{
	int	max;
	int	len;
	int	y;

	max = 0;
	y = 0;
	while (data()->map_old[y] != NULL)
	{
		len = ft_strlen(data()->map_old[y]);
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

static int	static_map_count_lines(char *filepath)
{
	int		fd;
	char	*line;
	int		linecount;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_end_program_error(SYSTEM);
	linecount = 0;
	line = ft_gnl(fd);
	while (line != NULL)
	{
		linecount++;
		free(line);
		line = ft_gnl(fd);
	}
	if (close(fd) == -1)
		exit_end_program_error(SYSTEM);
	return (linecount);
}

static void	static_map_replace_char1_with_char2(char *str, char c1, char c2)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c1)
			str[i] = c2;
		i++;
	}
}

void	map_read(char *filepath)
{
	int		fd;
	int		numberoflines;
	int		y;

	numberoflines = static_map_count_lines(filepath);
	data()->map_old = malloc(sizeof(char *) * (numberoflines + 1));
	if (data()->map_old == NULL)
		exit_end_program_error(SYSTEM);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_end_program_error(SYSTEM);
	y = 0;
	while (y < numberoflines)
	{
		data()->map_old[y] = ft_gnl(fd);
		if (data()->map_old[y] == NULL)
			exit_end_program_error(SYSTEM);
		static_map_replace_char1_with_char2(data()->map_old[y], '\n', '\0');
		y++;
	}
	data()->map_old[numberoflines] = NULL;
	if (close(fd) == -1)
		exit_end_program_error(SYSTEM);
	data()->map.height = numberoflines;
	data()->map.width = static_map_determine_max_y();
}
