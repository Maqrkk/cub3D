/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 09:32:20 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:28:13 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	This function will check if a key is held down and try to move the player
**	accordingly. Will return 1 if the player moved or rotated, 0 if not.
*/

int		move_player(t_data *data)
{
	t_ivector	movement;
	double		rotation;

	get_movement(&movement, &rotation, &data->keystates);
	if (movement.x == 0 && movement.y == 0 && rotation == 0)
		return (0);
	if (movement.y != 0)
		move_forward_or_backward(data, movement.y);
	if (movement.x != 0)
		move_sideways(data, movement.x);
	if (rotation != 0)
		rotate_player(&data->player, rotation);
	return (1);
}

/*
**	This function will rotate the player and the camera plane.
*/

void	rotate_player(t_player *player, double direction)
{
	double	rotation;

	rotation = direction * player->turn_speed;
	rotate_dvector(&player->dir, rotation);
	rotate_dvector(&player->plane, rotation);
}

/*
**	This function will attempt to move the player to a new position on the
**	y-axis of the direction ray. 1 is forward, -1 is backward.
*/

void	move_forward_or_backward(t_data *data, int direction)
{
	char		**map;
	double		speed;
	int			new_x;
	int			new_y;
	t_player	*player;

	player = &data->player;
	map = data->map.tiles;
	speed = direction * player->move_speed;
	new_x = (int)(player->pos.x + player->dir.x * speed);
	new_y = (int)(player->pos.y + player->dir.y * speed);
	if (map[(int)player->pos.y][new_x] != '1')
		player->pos.x += player->dir.x * speed;
	if (map[new_y][(int)player->pos.x] != '1')
		player->pos.y += player->dir.y * speed;
}

/*
**	This functon will attempt to move the player to a new position on the
**	x-axis of the direction ray. -1 for left, 1 for right.
*/

void	move_sideways(t_data *data, int direction)
{
	char		**map;
	double		speed;
	int			new_x;
	int			new_y;
	t_player	*player;

	player = &data->player;
	map = data->map.tiles;
	speed = direction * player->move_speed;
	new_x = (int)(player->pos.x + player->plane.x * speed);
	new_y = (int)(player->pos.y + player->plane.y * speed);
	if (map[(int)player->pos.y][new_x] != '1')
		player->pos.x += player->plane.x * speed;
	if (map[new_y][(int)player->pos.x] != '1')
		player->pos.y += player->plane.y * speed;
}

/*
**	This function captures if there is any key held down and set values
**	in the struct passed as argument accordingly. It also checks if the
**	mouse has been moved, and then resets that value.
*/

void	get_movement(t_ivector *movement, double *rotation, t_keystate *keys)
{
	movement->x = 0;
	movement->y = 0;
	if (keys->w == 1)
		movement->y += 1;
	if (keys->s == 1)
		movement->y -= 1;
	if (keys->a == 1)
		movement->x -= 1;
	if (keys->d == 1)
		movement->x += 1;
	*rotation = 0;
	if (keys->left == 1)
		*rotation -= 1;
	if (keys->right == 1)
		*rotation += 1;
	if (keys->mouse_rotation != 0)
	{
		*rotation += keys->mouse_rotation / 2;
		keys->mouse_rotation = 0;
	}
}
