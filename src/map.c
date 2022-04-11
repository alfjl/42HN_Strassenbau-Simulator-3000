# include "cub3d.h"

static int	determine_max_y(void)
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

// static void	static_exit_from_read(char **map_old, int error)
// {
// 	free(map_old);
// 	exit_error(NULL, error);
// }

int	count_lines(char *filepath)
{
	int		fd;
	char	*line;
	int		linecount;

	fd = open(filepath, O_RDONLY);
	// if (fd == -1)
	// 	exit_error(NULL, OPEN);
	linecount = 0;
	line = ft_gnl(fd);
	while (line != NULL)
	{
		linecount++;
		free(line);
		line = ft_gnl(fd);
	}
	// if (close(fd) == -1)
	// 	exit_error(NULL, CLOSE);
	return (linecount);
}

void	replace_char1_with_char2(char *str, char c1, char c2)
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

void	read_map(char *filepath)
{
	int		fd;
	int		numberoflines;
	int		y;

	numberoflines = count_lines(filepath);
	data()->map_old = malloc(sizeof(char *) * (numberoflines + 1));
	// if (data()->map_old == NULL)
	// 	exit_error(NULL, MALLOC);
	fd = open(filepath, O_RDONLY);
	// if (fd == -1)
	// 	static_exit_from_read(data->map_old, OPEN);
	y = 0;
	while (y < numberoflines)
	{
		data()->map_old[y] = ft_gnl(fd);
		// if (data()->map_old[y] == NULL)
		// 	exit_error(data, MALLOC);
		replace_char1_with_char2(data()->map_old[y], '\n', '\0');
		y++;
	}
	data()->map_old[numberoflines] = NULL;
	// if (close(fd) == -1)
	// 	static_exit_from_read(data->map_old, CLOSE);
	// check_map(data, numberoflines);
	data()->grid.height = numberoflines;
	data()->grid.width = determine_max_y();
	data()->map.grid = data()->map_old; //workaround to get map into the new struct format
}
