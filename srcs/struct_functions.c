/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:27:01 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 11:35:52 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/*
**	This function will clean the struct, and call the other clean functions
**	after.
*/

void		clean_data_struct(t_data *data)
{
	data->mlx = NULL;
	data->window = NULL;
	data->img1.img = NULL;
	data->img1.addr = NULL;
	data->img2.img = NULL;
	data->img2.addr = NULL;
	data->active_image = 2;
	data->keystates.left = 0;
	data->keystates.right = 0;
	data->keystates.w = 0;
	data->keystates.a = 0;
	data->keystates.s = 0;
	data->keystates.d = 0;
	data->keystates.mouse_rotation = 0;
	data->objects.amount = 0;
	data->objects.objects = NULL;
	clean_map_struct(&data->map);
	clean_raycaster_struct(&data->raycaster);
	clean_textures_struct(&data->textures);
	clean_player_struct(&data->player);
}

/*
**	This function sets all the map data to their initial values.
*/

void		clean_map_struct(t_map *map)
{
	map->resolution.x = 0;
	map->resolution.y = 0;
	map->size.x = 0;
	map->size.y = 0;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->tiles = make_empty_tileset();
	if (map->tiles == NULL)
		report_error("A malloc failed.", NULL);
	map->parser.fd = 0;
	map->parser.phase = 0;
	map->parser.line = NULL;
	map->parser.floor_set = 0;
	map->parser.ceiling_set = 0;
}

/*
**	This function sets all the raycaster data to their initial values.
*/

void		clean_raycaster_struct(t_raycast *rc)
{
	rc->camera_x = 0;
	rc->ray_dir.x = 0;
	rc->ray_dir.y = 0;
	rc->delta_dist.x = 0;
	rc->delta_dist.y = 0;
	rc->step.x = 0;
	rc->step.y = 0;
	rc->dist_buffer = NULL;
}

/*
**	This function sets all the textures to the value NULL.
*/

void		clean_textures_struct(t_textures *textures)
{
	textures->north.file = NULL;
	textures->north.img.img = NULL;
	textures->east.file = NULL;
	textures->east.img.img = NULL;
	textures->south.file = NULL;
	textures->south.img.img = NULL;
	textures->west.file = NULL;
	textures->west.img.img = NULL;
	textures->sprite.file = NULL;
	textures->sprite.img.img = NULL;
	textures->floor.file = NULL;
	textures->floor.img.img = NULL;
	textures->ceiling.file = NULL;
	textures->ceiling.img.img = NULL;
}

/*
**	This function sets all the player variables to their initial values.
*/

void		clean_player_struct(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->map.x = 0;
	player->map.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->move_speed = 0.08;
	player->turn_speed = 0.04;
}
