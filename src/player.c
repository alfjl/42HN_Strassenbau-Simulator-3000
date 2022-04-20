#include "cub3d.h"

static void	static_player_update(float *x, float dx, float *y, float dy)
{
	float	new_x;
	float	new_y;

	new_x = *x + dx;
	new_y = *y + dy;
	if (!is_wall(*y, (*x + dx)))
	{
		if (new_x >= 0 && new_x < data()->map.width)
			*x = new_x;
	}
	if (!is_wall((*y + dy), *x))
	{
		if (new_y >= 0 && new_y < data()->map.height)
			*y = new_y;
	}
}

void	player_update_position(t_keys *keys)
{
	t_player	*player;

	player = &data()->player;
	player->dx = cos(player->angle) * STEP;
	player->dy = sin(player->angle) * STEP;
	if (keys->forwards)
		static_player_update(&player->x, player->dx, &player->y, player->dy);
	if (keys->backwards)
		static_player_update(&player->x, -player->dx, &player->y, -player->dy);
	if (keys->leftwards)
		static_player_update(&player->x, player->dy, &player->y, -player->dx);
	if (keys->rightwards)
		static_player_update(&player->x, -player->dy, &player->y, player->dx);
	if (keys->turnleft)
		player->angle = radian_limits(player->angle - STEP_A);
	if (keys->turnright)
		player->angle = radian_limits(player->angle + STEP_A);
}
