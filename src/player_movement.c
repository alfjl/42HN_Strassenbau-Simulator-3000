#include "cub3d.h"

void	player_update_z_position(void)
{
	t_player	*player;

	player = &data()->player;
	if (player->is_jumping && player->dz < 0)
		player->dz = 0;
	else if (player->is_jumping && player->dz < JUMP_DELTA)
		player->dz += GRAVITY;
	else if (player->dz > 0)
	{
		player->is_jumping = false;
		player->dz -= GRAVITY;
		if (player->dz < 0)
			player->dz = 0;
	}
}

static void	static_player_set_status(t_controls *controls)
{
	if (data()->player.status == HITTING)
		return ;
	else if (controls->forwards || controls->backwards || controls->leftwards
		|| controls->rightwards)
		data()->player.status = WALKING;
	else
		data()->player.status = IDLE;
}

static bool	static_player_is_wall(float y, float x)
{
	float	min_y;
	float	max_y;
	float	min_x;
	float	max_x;

	if (!COLLISION_ENABLED)
		return (false);
	min_y = y - COLLISION_DISTANCE;
	max_y = y + COLLISION_DISTANCE;
	min_x = x - COLLISION_DISTANCE;
	max_x = x + COLLISION_DISTANCE;
	if (max_y < data()->map.height && min_y >= 0 && max_x < data()->map.width
		&& min_x >= 0)
	{
		if (data()->map.grid[(int)min_y][(int)min_x] == WALL)
			return (true);
		if (data()->map.grid[(int)max_y][(int)max_x] == WALL)
			return (true);
		if (data()->map.grid[(int)min_y][(int)max_x] == WALL)
			return (true);
		if (data()->map.grid[(int)max_y][(int)min_x] == WALL)
			return (true);
		return (false);
	}
	return (true);
}

static void	static_player_update(float *x, float dx, float *y, float dy)
{
	float	new_x;
	float	new_y;
	t_map	*map;

	map = &data()->map;
	new_x = *x + dx;
	new_y = *y + dy;
	if (!static_player_is_wall(*y, (*x + dx)))
	{
		if (new_x >= 0 && new_x < map->width) //check for void
			*x = new_x;
	}
	if (!static_player_is_wall((*y + dy), *x))
	{
		if (new_y >= 0 && new_y < map->height)
			*y = new_y;
	}
}

void	player_update_position(t_controls *controls)
{
	t_player	*player;
	float		*x;
	float		*y;
	float		dx;
	float		dy;

	player = &data()->player;
	calculate_pos_delta();
	x = &player->x;
	y = &player->y;
	dx = player->dx;
	dy = player->dy;
	if (controls->forwards)
		static_player_update(x, dx, y, dy);
	if (controls->backwards)
		static_player_update(x, -dx, y, -dy);
	if (controls->leftwards)
		static_player_update(x, dy, y, -dx);
	if (controls->rightwards)
		static_player_update(x, -dy, y, dx);
	if (controls->turnleft || controls->mouse_left)
		player->angle = radian_limits(player->angle - player->turn_speed);
	if (controls->turnright || controls->mouse_right)
		player->angle = radian_limits(player->angle + player->turn_speed);
	static_player_set_status(controls);
}
