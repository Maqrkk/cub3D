/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 09:03:12 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:28:31 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	This is the main control function of the raycaster.
*/

void		cast_ray(int column, t_data *data)
{
	t_raycast	*rc;
	t_player	*player;

	rc = &data->raycaster;
	player = &data->player;
	prepare_raycaster(data, column);
	find_wall_hit(data);
	calculate_distance(rc, player, column);
	find_wall_x(data);
}

/*
**	This function will be called once before the game, to set some initial
**	values for the raycaster.
*/

void		init_camera(t_player *player)
{
	if (player->dir.x == 0)
		player->plane.y = 0;
	else
		player->plane.y = (player->dir.x == 1) ? 0.66 : -0.66;
	if (player->dir.y == 0)
		player->plane.x = 0;
	else
		player->plane.x = (player->dir.y == -1) ? 0.66 : -0.66;
}

/*
**	This will initialise all the values for the current ray we're casting.
*/

void		prepare_raycaster(t_data *data, int column)
{
	t_player	*player;
	t_raycast	*rc;

	player = &data->player;
	rc = &data->raycaster;
	rc->camera_x = 2 * (float)column / (float)data->map.resolution.x - 1;
	multiply_dvector(&rc->ray_dir, &player->plane, rc->camera_x);
	add_dvectors(&rc->ray_dir, &rc->ray_dir, &player->dir);
	player->map.x = (int)player->pos.x;
	player->map.y = (int)player->pos.y;
	rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
	rc->hit = 0;
	set_direction_variables(rc, player);
}

/*
**	This sets variables depending on the direction of the ray.
*/

void		set_direction_variables(t_raycast *rc, t_player *player)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (player->pos.x - player->map.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (player->map.x + 1.0 - player->pos.x) *
			rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (player->pos.y - player->map.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (player->map.y + 1.0 - player->pos.y) *
			rc->delta_dist.y;
	}
}

/*
**	This function will do the actual ray-casting, finds when a wall is hit.
*/

void		find_wall_hit(t_data *data)
{
	t_raycast	*rc;
	t_player	*player;

	rc = &data->raycaster;
	player = &data->player;
	while (rc->hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			player->map.x += rc->step.x;
			rc->side = (rc->step.x == 1) ? 0 : 2;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			player->map.y += rc->step.y;
			rc->side = (rc->step.y == 1) ? 1 : 3;
		}
		if (*(*(data->map.tiles + player->map.y) + player->map.x) == '1')
			rc->hit = 1;
	}
}
