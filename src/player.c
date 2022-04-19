#include "cub3d.h"

static void	static_player_update(float *straight, float dstraight, float *cross,
	float dcross)
{
	float	new_x;
	float	new_y;

	new_x = *straight + dstraight;
	new_y = *cross + dcross;
	if (!is_wall(*cross,
			(*straight + dstraight)))
	{
		if (new_x >= 0 && new_x < data()->map.width)
			*straight = new_x;
	}
	if (!is_wall((*cross + dcross),
			*straight))
	{
		if (new_y >= 0 && new_y < data()->map.height)
			*cross = new_y;
	}
}

void	player_update_position(t_keys *keys)
{
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
	if (keys->forwards)
		static_player_update(&data()->player.x, data()->player.dx,
			&data()->player.y, data()->player.dy);
	if (keys->backwards)
		static_player_update(&data()->player.x, -data()->player.dx,
			&data()->player.y, -data()->player.dy);
	if (keys->leftwards)
		static_player_update(&data()->player.x, data()->player.dy,
			&data()->player.y, -data()->player.dx);
	if (keys->rightwards)
		static_player_update(&data()->player.x, -data()->player.dy,
			&data()->player.y, data()->player.dx);
	if (keys->turnleft)
		data()->player.angle = radian_limits(data()->player.angle - STEP_A);
	if (keys->turnright)
		data()->player.angle = radian_limits(data()->player.angle + STEP_A);
}
