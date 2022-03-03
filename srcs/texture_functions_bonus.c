/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 13:03:52 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:59:29 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <mlx.h>
#include <stdlib.h>

/*
**	This function will return the corresponding texture for whichever wall
**	was hit, depending on the 'side' variable.
*/

t_texture	*get_texture_for_wall(t_data *data)
{
	t_raycast	*rc;
	t_textures	*textures;

	rc = &data->raycaster;
	textures = &data->textures;
	if (rc->side == 0)
		return (&textures->west);
	else if (rc->side == 1)
		return (&textures->north);
	else if (rc->side == 2)
		return (&textures->east);
	return (&textures->south);
}

/*
**	This function will initialise the textures needed for the program.
*/

void		init_textures(t_data *data, t_textures *textures)
{
	int			i;
	t_texture	*tex;

	i = 0;
	while (i < 5)
	{
		tex = get_texture_by_id(textures, i);
		init_texture(data, tex);
		i++;
	}
	if (textures->floor.file != NULL)
		init_texture(data, &textures->floor);
	if (textures->ceiling.file != NULL)
		init_texture(data, &textures->ceiling);
}

/*
**	This function will initialise a single texture.
*/

void		init_texture(t_data *data, t_texture *tex)
{
	if (check_file_extension(tex->file, ".png") == 1)
		tex->img.img = mlx_png_file_to_image(data->mlx, tex->file,
				&tex->width, &tex->height);
	else
		tex->img.img = mlx_xpm_file_to_image(data->mlx, tex->file,
				&tex->width, &tex->height);
	if (tex->img.img == NULL)
		report_error("Incorrect texture.", data);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_length, &tex->img.endian);
}

/*
**	This is a helper function to get a texture, to make it easier to loop
**	over them one by one.
*/

t_texture	*get_texture_by_id(t_textures *textures, int id)
{
	if (id == 0)
		return (&textures->north);
	else if (id == 1)
		return (&textures->east);
	else if (id == 2)
		return (&textures->south);
	else if (id == 3)
		return (&textures->west);
	else if (id == 4)
		return (&textures->sprite);
	else if (id == 5)
		return (&textures->floor);
	else
		return (&textures->ceiling);
}
