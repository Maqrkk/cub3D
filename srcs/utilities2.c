/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 11:11:04 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:29:36 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/*
**	This function will check if the file passed is a .png or .xpm image.
**	Returns 1 if it is, 0 if not.
*/

int		is_image_file(char *file)
{
	if (check_file_extension(file, ".png") == 1)
		return (1);
	if (check_file_extension(file, ".xpm") == 1)
		return (1);
	return (0);
}

/*
**	This function will malloc a double array for raycasting.
*/

void	init_dist_buffer(t_data *data, int size)
{
	t_raycast	*rc;

	rc = &data->raycaster;
	rc->dist_buffer = malloc(sizeof(double) * size);
	if (rc->dist_buffer == NULL)
		report_error("A malloc failed.", data);
}

/*
**	This function will calculate the distance (without taking the square
**	root) of all the sprites, so we can sort it later.
*/

void	calculate_sprite_distances(t_objects *objects, t_player *player)
{
	int			i;
	t_object	*current;
	double		dist_x;
	double		dist_y;

	i = 0;
	while (i < objects->amount)
	{
		current = *(objects->objects + i);
		dist_x = current->pos.x - player->pos.x;
		dist_y = current->pos.y - player->pos.y;
		current->dist = dist_x * dist_x + dist_y * dist_y;
		i++;
	}
}

/*
**	This function will sort the sprites based on their distance from the
**	player, furthest first.
*/

void	sort_sprites(t_objects *objects)
{
	int			i;
	int			j;
	t_object	**list;
	t_object	*current;

	list = objects->objects;
	i = 0;
	while (i < objects->amount)
	{
		current = list[i];
		j = i - 1;
		while (j >= 0 && list[j]->dist < current->dist)
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = current;
		i++;
	}
}
