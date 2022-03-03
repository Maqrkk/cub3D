/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 13:57:14 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:28:38 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	This function calculates the distance to the wall that has been hit,
**	perpendicular to the camera plane.
*/

void		calculate_distance(t_raycast *rc, t_player *player, int column)
{
	double	tmp;

	if (rc->side % 2 == 0)
	{
		tmp = player->map.x - player->pos.x + (1 - rc->step.x) / 2;
		rc->perp_dist = tmp / rc->ray_dir.x;
	}
	else
	{
		tmp = player->map.y - player->pos.y + (1 - rc->step.y) / 2;
		rc->perp_dist = tmp / rc->ray_dir.y;
	}
	*(rc->dist_buffer + column) = rc->perp_dist;
}

/*
**	This function will calculate the X-coordinate where the wall was hit. This
**	is necessary to know what part of the texture to draw.
*/

void		find_wall_x(t_data *data)
{
	t_raycast	*rc;
	t_player	*player;

	rc = &data->raycaster;
	player = &data->player;
	if (rc->side % 2 == 0)
		rc->wall_x = player->pos.y + rc->perp_dist * rc->ray_dir.y;
	else
		rc->wall_x = player->pos.x + rc->perp_dist * rc->ray_dir.x;
	rc->wall_x -= floor(rc->wall_x);
	if (rc->side > 1)
		rc->wall_x = 1 - rc->wall_x;
}
