#include "cub3d.h"
#include <sys/time.h>
#include <time.h>

static long	static_get_current_time(void)
{
	long			current_time;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL); //delete c file
	current_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (current_time);
}

void	timedifference(char *str)
{
	long	current_time;
	long	delta;

	current_time = clock(); //delete c file
	delta = current_time - data()->time;
	data()->time = current_time;
	printf("%s time:\t%lu clocks\n", str, delta);
}

void	fps_to_window_buffer(void)
{
	long	current_time;
	long	elapse_time;
	int		fps;
	char	*str;

	if (data()->fps.first)
	{
		data()->fps.last_time = static_get_current_time();
		data()->fps.first = false;
	}
	current_time = static_get_current_time();
	elapse_time = current_time - data()->fps.last_time;
	fps = 1000.0 / elapse_time;
	data()->fps.last_time = current_time;
	str = ft_itoa(fps);
	mlx_string_put(data()->mlx, data()->win, 20, 500, ORANGE, str);
	mlx_string_put(data()->mlx, data()->win, 40, 500, ORANGE, "FPS");
	free(str);
}
