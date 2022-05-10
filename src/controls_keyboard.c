/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:52:46 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:52:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	static_keyboard_key_release_hook(int keycode, t_controls *controls)
{
	if (keycode == W_KEY)
		controls->forwards = false;
	if (keycode == S_KEY)
		controls->backwards = false;
	if (keycode == A_KEY)
		controls->leftwards = false;
	if (keycode == D_KEY)
		controls->rightwards = false;
	if (keycode == LEFT_KEY)
		controls->turnleft = false;
	if (keycode == RIGHT_KEY)
		controls->turnright = false;
	if (SPRINT_ENABLED && keycode == SHIFT_KEY)
		data()->player.step_size = MOVE_STEP;
	return (EXIT_SUCCESS);
}

static int	static_keyboard_key_press_hook(int keycode, t_controls *controls)
{
	if (keycode == ESC_KEY)
		exit_end_program_success();
	if (keycode == W_KEY)
		controls->forwards = true;
	if (keycode == S_KEY)
		controls->backwards = true;
	if (keycode == A_KEY)
		controls->leftwards = true;
	if (keycode == D_KEY)
		controls->rightwards = true;
	if (keycode == LEFT_KEY)
		controls->turnleft = true;
	if (keycode == RIGHT_KEY)
		controls->turnright = true;
	if (CROUCH_ENABLED && keycode == CTRL_KEY && data()->player.dz == 0)
		data()->player.dz = CROUCH_DELTA;
	else if (CROUCH_ENABLED && keycode == CTRL_KEY && !(data()->player.dz > 0))
		data()->player.dz = 0;
	if (JUMP_ENABLED && keycode == SPACE_KEY && !(data()->player.dz > 0))
		data()->player.is_jumping = true;
	if (SPRINT_ENABLED && keycode == SHIFT_KEY)
		data()->player.step_size = MOVE_STEP * PLAYER_SPRINT_FACTOR;
	if (DOORS_ENABLED)
		doors_interact(keycode);
	return (EXIT_SUCCESS);
}

void	controls_keyboard(t_controls *controls)
{
	void	*win;

	win = data()->win;
	mlx_hook(win, KeyPress, KeyPressMask, static_keyboard_key_press_hook,
		controls);
	mlx_hook(win, KeyRelease, KeyReleaseMask, static_keyboard_key_release_hook,
		controls);
}
