/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 13:22:24 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:27:01 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

/*
**	Will call the raytracing functions to draw an image column by column.
*/

void			draw_frame(t_data *data)
{
	int		current_x;
	t_img	*new_image;

	new_image = get_new_image(data);
	current_x = 0;
	draw_planes(new_image, data);
	while (current_x < data->map.resolution.x)
	{
		cast_ray(current_x, data);
		draw_column(new_image, data, current_x, data->map.resolution.y);
		current_x++;
	}
	draw_sprites(new_image, data);
	if (data->bitmap_mode == 0)
		set_new_image(data);
}

/*
**	Simple function to draw a single pixel.
*/

void			draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

/*
**	Simple function to return the color of a pixel of an image.
*/

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

/*
**	This function will draw the column with the information from the raycaster.
*/

void			draw_column(t_img *img, t_data *data, int x, int height)
{
	t_draw		draw;

	draw.x = x;
	draw.wall_height = (int)(height / data->raycaster.perp_dist);
	draw.wall_start = -draw.wall_height / 2 + height / 2;
	if (draw.wall_start < 0)
		draw.wall_start = 0;
	draw.wall_end = draw.wall_height / 2 + height / 2;
	if (draw.wall_end > height - 1)
		draw.wall_end = height - 1;
	draw.texture = get_texture_for_wall(data);
	draw.screen_height = height;
	draw_wall(img, &draw, data->raycaster.wall_x);
}

/*
**	This function will draw the wall.
*/

void			draw_wall(t_img *img, t_draw *draw, double wall_x)
{
	int			i;
	int			tex_y;
	int			color;
	double		step;
	double		tex_pos;

	draw->tex_x = (int)(wall_x * (double)draw->texture->width);
	step = 1.0 * draw->texture->height / draw->wall_height;
	tex_pos = (draw->wall_start - draw->screen_height / 2 + draw->wall_height
			/ 2) * step;
	i = draw->wall_start;
	while (i <= draw->wall_end)
	{
		tex_y = (int)tex_pos & (draw->texture->height - 1);
		tex_pos += step;
		color = get_pixel(&draw->texture->img, draw->tex_x, tex_y);
		draw_pixel(img, draw->x, i, color);
		i++;
	}
}
