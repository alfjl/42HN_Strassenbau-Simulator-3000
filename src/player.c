# include "cub3d.h"

static void	static_player_update_forwards(void)
{
	if (!is_wall(data()->player.y, (data()->player.x + data()->player.dx * DISTANCE_FACTOR)))
		data()->player.x += data()->player.dx;
	if (!is_wall((data()->player.y + data()->player.dy * DISTANCE_FACTOR), data()->player.x))
		data()->player.y += data()->player.dy;
}

static void	static_player_update_backwards(void)
{
	if (!is_wall(data()->player.y, (data()->player.x - data()->player.dx)))
		data()->player.x -= data()->player.dx;
	if (!is_wall((data()->player.y - data()->player.dy), data()->player.x))
		data()->player.y -= data()->player.dy;
}

static void	static_player_update_turnleft(void)
{
	data()->player.angle -= STEP_A;
	if (data()->player.angle < 0)
		data()->player.angle += 2 * PI;
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
}

static void	static_player_update_turnright(void)
{
	data()->player.angle += STEP_A;
	if (data()->player.angle > 2 * PI)
		data()->player.angle -= 2 * PI;
	data()->player.dx = cos(data()->player.angle) * STEP;
	data()->player.dy = sin(data()->player.angle) * STEP;
}

void	player_update_position(t_keys *keys)
{
	if (keys->forwards)
		static_player_update_forwards();
	if (keys->turnleft)
		static_player_update_turnleft();
	if (keys->backwards)
		static_player_update_backwards();
	if (keys->turnright)
		static_player_update_turnright();
}