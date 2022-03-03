/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 15:48:39 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:29:06 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	This function calculates the transform needed for drawing sprites.
*/

void		calculate_transform(t_object *sprite, t_player *player,
				t_sdraw *draw)
{
	t_dvector	sprite_pos;
	double		inverse_determinant;

	sprite_pos.x = sprite->pos.x - player->pos.x;
	sprite_pos.y = sprite->pos.y - player->pos.y;
	inverse_determinant = 1.0 / (player->plane.x * player->dir.y -
			player->dir.x * player->plane.y);
	draw->transform.x = inverse_determinant * (player->dir.y * sprite_pos.x -
			player->dir.x * sprite_pos.y);
	draw->transform.y = inverse_determinant * (-player->plane.y * sprite_pos.x +
			player->plane.x * sprite_pos.y);
}

/*
**	This function calculates the dimensions of the sprite to be drawn.
*/

void		calculate_dimensions(t_data *data, t_sdraw *draw)
{
	t_ivector	*res;

	res = &data->map.resolution;
	draw->screen_x = (int)((res->x / 2) *
			(1 + draw->transform.x / draw->transform.y));
	draw->size.y = (int)fabs(res->y / draw->transform.y);
	draw->start.y = (-draw->size.y / 2) + (res->y / 2);
	draw->start.y = (draw->start.y < 0) ? 0 : draw->start.y;
	draw->end.y = (draw->size.y / 2) + (res->y / 2);
	draw->end.y = (draw->end.y >= res->y) ? res->y - 1 : draw->end.y;
	draw->size.x = draw->size.y;
	draw->start.x = (-draw->size.x / 2) + draw->screen_x;
	draw->start.x = (draw->start.x < 0) ? 0 : draw->start.x;
	draw->end.x = (draw->size.x / 2) + draw->screen_x;
	draw->end.x = (draw->end.x >= res->x) ? res->x - 1 : draw->end.x;
}
