/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:13:01 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 08:45:44 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

/*
**	This function registers when a key is pressed, and will update the
**	appropriate keystate, or close the game in case of the escape key.
*/

int		key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESCAPE)
		close_game(data);
	else if (keycode == KEY_A)
		data->keystates.a = 1;
	else if (keycode == KEY_S)
		data->keystates.s = 1;
	else if (keycode == KEY_D)
		data->keystates.d = 1;
	else if (keycode == KEY_W)
		data->keystates.w = 1;
	else if (keycode == KEY_LEFT)
		data->keystates.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keystates.right = 1;
	return (1);
}

/*
**	This function registers when a key is released, and will update the
**	keystate accordingly.
*/

int		key_release(int keycode, t_data *data)
{
	if (keycode == KEY_A)
		data->keystates.a = 0;
	else if (keycode == KEY_S)
		data->keystates.s = 0;
	else if (keycode == KEY_D)
		data->keystates.d = 0;
	else if (keycode == KEY_W)
		data->keystates.w = 0;
	else if (keycode == KEY_LEFT)
		data->keystates.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keystates.right = 0;
	return (1);
}

/*
**	This function will be triggered every frame. It will check if the player
**	has moved, and only then draw a new frame.
*/

int		loop_game(t_data *data)
{
	int		moved;

	moved = move_player(data);
	if (moved)
		draw_frame(data);
	return (1);
}
