/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 12:48:01 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:06:40 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

/*
**	This function will make sure we close our game cleanly.
*/

int			close_game(t_data *data)
{
	if (data->img1.img != NULL)
		mlx_destroy_image(data->mlx, data->img1.img);
	if (data->img2.img != NULL)
		mlx_destroy_image(data->mlx, data->img2.img);
	if (data->window != NULL)
		mlx_destroy_window(data->mlx, data->window);
	if (data->map.parser.fd >= 3)
		close(data->map.parser.fd);
	if (data->bitmap_fd >= 3)
		close(data->bitmap_fd);
	if (data->map.tiles != NULL)
		free_string_array(data->map.tiles);
	if (data->map.parser.line != NULL)
		free(data->map.parser.line);
	destroy_textures(data, &data->textures);
	destroy_objects(data);
	exit(1);
	return (1);
}

/*
**	This function will free the textures if they are allocated.
*/

void		destroy_textures(t_data *data, t_textures *textures)
{
	int			i;
	t_texture	*current_texture;

	i = 0;
	while (i < 5)
	{
		current_texture = get_texture_by_id(textures, i);
		if (current_texture->file != NULL)
		{
			free(current_texture->file);
			if (current_texture->img.img != NULL)
				mlx_destroy_image(data->mlx, current_texture->img.img);
		}
		i++;
	}
}

/*
**	This function will free any objects that are allocated.
*/

void		destroy_objects(t_data *data)
{
	int			i;
	t_objects	*objects;
	t_object	*object;

	objects = &data->objects;
	i = 0;
	while (i < objects->amount)
	{
		object = *(objects->objects + i);
		free(object);
		i++;
	}
	free(objects->objects);
}
