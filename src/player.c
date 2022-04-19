#include "cub3d.h"

static void	static_player_update_forwards(void)
{
	float	new_x;
	float	new_y;
	
	if (!is_wall(data()->player.y,
			(data()->player.x + data()->player.dx)))
	{
		new_x = data()->player.x + data()->player.dx;
		if (new_x >= 0 && new_x < data()->map.width)
			data()->player.x = new_x;
	}
	if (!is_wall((data()->player.y + data()->player.dy),
			data()->player.x))
	{
		new_y = data()->player.y + data()->player.dy;
		if (new_y >= 0 && new_y < data()->map.height)
			data()->player.y = new_y;
	}
}

static void	static_player_update_backwards(void)
{
	float	new_x;
	float	new_y;

	if (!is_wall(data()->player.y, (data()->player.x - data()->player.dx)))
	{
		new_x = data()->player.x - data()->player.dx;
		if (new_x >= 0 && new_x < data()->map.width)
			data()->player.x = new_x;
	}
	if (!is_wall((data()->player.y - data()->player.dy), data()->player.x))
	{
		new_y = data()->player.y - data()->player.dy;
		if (new_y >= 0 && new_y < data()->map.height)
			data()->player.y = new_y;
	}
}

static void	static_player_update_leftwards(void)
{
	float	new_x;
	float	new_y;
	
	new_x = data()->player.x + data()->player.dy;
	new_y = data()->player.y - data()->player.dx;
	if (!is_wall(data()->player.y, data()->player.x + data()->player.dy))
	{
		if (new_x >= 0 && new_x < data()->map.width)
			data()->player.x = new_x;
	}
	if (!is_wall(data()->player.y - data()->player.dx, data()->player.x))
	{
		if (new_y >= 0 && new_y < data()->map.height)
			data()->player.y = new_y;
	}
}

static void	static_player_update_rightwards(void)
{
	float	new_x;
	float	new_y;
	
	new_x = data()->player.x - data()->player.dy;
	new_y = data()->player.y + data()->player.dx;
	if (!is_wall(data()->player.y, data()->player.x - data()->player.dy))
	{
		if (new_x >= 0 && new_x < data()->map.width)
			data()->player.x = new_x;
	}
	if (!is_wall(data()->player.y + data()->player.dx, data()->player.x))
	{
		if (new_y >= 0 && new_y < data()->map.height)
			data()->player.y = new_y;
	}
}

static void	static_player_update_turnleft(void)
{
	data()->player.angle -= STEP_A;
	if (data()->player.angle < 0)
		data()->player.angle += 2 * PI;
}

static void	static_player_update_turnright(void)
{
	data()->player.angle += STEP_A;
	if (data()->player.angle > 2 * PI)
		data()->player.angle -= 2 * PI;
}

void	player_update_position(t_keys *keys)
{
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
	if (keys->forwards)
		static_player_update_forwards();
	if (keys->backwards)
		static_player_update_backwards();
	if (keys->leftwards)
		static_player_update_leftwards();
	if (keys->rightwards)
		static_player_update_rightwards();
	if (keys->turnleft)
		static_player_update_turnleft();
	if (keys->turnright)
		static_player_update_turnright();
}
