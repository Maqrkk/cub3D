/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions3_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 14:44:13 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 16:09:40 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
**	This function will draw one single horizontal line for the floor and the
**	ceiling at once.
*/

void		draw_plane_line(t_img *img, t_data *data, t_pdraw *draw, int y)
{
	int			x;
	t_textures	*textures;
	int			color;

	textures = &data->textures;
	x = 0;
	while (x < data->map.resolution.x)
	{
		draw->cell.x = (int)draw->pos.x;
		draw->cell.y = (int)draw->pos.y;
		add_dvectors(&draw->pos, &draw->pos, &draw->step);
		color = get_floor_color(data, draw);
		draw_pixel(img, x, y, color);
		color = get_ceiling_color(data, draw);
		draw_pixel(img, x, data->map.resolution.y - y - 1, color);
		x++;
	}
}

/*
**	Quick helper function to get the color of the ceiling, whether from
**	plain color or texture.
*/

int			get_ceiling_color(t_data *data, t_pdraw *draw)
{
	t_ivector	tex;

	if (data->map.ceil_color != -1)
		return (data->map.ceil_color);
	tex.x = (int)(data->textures.ceiling.width * (draw->pos.x -
				draw->cell.x)) & (data->textures.ceiling.width - 1);
	tex.y = (int)(data->textures.ceiling.height * (draw->pos.y -
				draw->cell.y)) & (data->textures.ceiling.height - 1);
	return (get_pixel(&data->textures.ceiling.img, tex.x, tex.y));
}

/*
**	Quick helper function to get the color of the floor, whether from
**	plain color or texture.
*/

int			get_floor_color(t_data *data, t_pdraw *draw)
{
	t_ivector	tex;

	if (data->map.floor_color != -1)
		return (data->map.floor_color);
	tex.x = (int)(data->textures.floor.width * (draw->pos.x -
				draw->cell.x)) & (data->textures.floor.width - 1);
	tex.y = (int)(data->textures.floor.height * (draw->pos.y -
				draw->cell.y)) & (data->textures.floor.height - 1);
	return (get_pixel(&data->textures.floor.img, tex.x, tex.y));
}
