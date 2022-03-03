/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 11:24:42 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:28:22 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>

/*
**	This function creates a new object with a certain position and returns
**	a pointer to it.
*/

t_object	*create_object(double x, double y, t_texture *sprite)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->pos.x = x;
	new->pos.y = y;
	new->sprite = sprite;
	return (new);
}

/*
**	This function inserts a new object in the objects struct.
*/

void		insert_object_in_struct(t_data *data, t_object *new)
{
	t_objects	*objects;
	t_object	**old_objects;
	int			i;

	objects = &data->objects;
	old_objects = objects->objects;
	objects->objects = malloc(sizeof(t_object *) * (objects->amount + 1));
	if (objects->objects == NULL)
		report_error("A malloc failed.", data);
	i = 0;
	while (i < objects->amount)
	{
		*(objects->objects + i) = *(old_objects + i);
		i++;
	}
	*(objects->objects + i) = new;
	objects->amount++;
	free(old_objects);
}
