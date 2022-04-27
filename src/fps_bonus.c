#include "cub3d.h"
#include <sys/time.h>

static long	static_fps_get_current_time(void)
{
	long			current_time;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL); //delete c file
	current_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (current_time);
}

void	fps_to_window_buffer(void)
{
	long		current_time;
	static long	last_time = 0;
	long		elapse_time;
	int			fps;
	char		*str;

	if (last_time == 0)
		last_time = static_fps_get_current_time();
	current_time = static_fps_get_current_time();
	elapse_time = current_time - last_time;
	fps = 1000.0 / elapse_time;
	last_time = current_time;
	str = ft_itoa(fps);
	mlx_string_put(data()->mlx, data()->win, 20, 500, ORANGE, str);
	mlx_string_put(data()->mlx, data()->win, 40, 500, ORANGE, "FPS");
	free(str);
}
