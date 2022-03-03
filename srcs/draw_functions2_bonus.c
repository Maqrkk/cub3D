/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_functions2_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 10:51:58 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 16:09:20 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
**	This function will draw the ceiling and floor using colors.
*/

void		draw_planes_simple(t_img *img, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->resolution.y / 2)
	{
		x = 0;
		while (x < map->resolution.x)
		{
			draw_pixel(img, x, y, map->ceil_color);
			draw_pixel(img, x, y + map->resolution.y / 2, map->floor_color);
			x++;
		}
		y++;
	}
}

/*
**	This function will draw the floor and ceiling with textures. Will instead
**	call draw_planes_simple if both are a color and not a texture.
*/

void		draw_planes(t_img *img, t_data *data)
{
	t_pdraw		draw;
	int			y;
	int			p;

	if (data->map.floor_color != -1 && data->map.ceil_color != -1)
		return (draw_planes_simple(img, &data->map));
	sub_dvectors(&draw.ray1, &data->player.dir, &data->player.plane);
	add_dvectors(&draw.ray2, &data->player.dir, &data->player.plane);
	draw.pos_z = 0.5 * data->map.resolution.y;
	y = data->map.resolution.y - 1;
	while (y > data->map.resolution.y / 2 - 1)
	{
		p = y - data->map.resolution.y / 2;
		draw.row_distance = draw.pos_z / p;
		draw.step.x = draw.row_distance * (draw.ray2.x - draw.ray1.x) /
			data->map.resolution.x;
		draw.step.y = draw.row_distance * (draw.ray2.y - draw.ray1.y) /
			data->map.resolution.x;
		draw.pos.x = data->player.pos.x + draw.row_distance * draw.ray1.x;
		draw.pos.y = data->player.pos.y + draw.row_distance * draw.ray1.y;
		draw_plane_line(img, data, &draw, y);
		y--;
	}
}

/*
**	This function will handle the drawing of the sprites.
*/

void		draw_sprites(t_img *img, t_data *data)
{
	t_raycast	*rc;
	t_object	*current;
	int			i;

	rc = &data->raycaster;
	calculate_sprite_distances(&data->objects, &data->player);
	sort_sprites(&data->objects);
	i = 0;
	while (i < data->objects.amount)
	{
		current = *(data->objects.objects + i);
		draw_single_sprite(img, current, data);
		i++;
	}
}

/*
**	This function will draw a single sprite.
*/

void		draw_single_sprite(t_img *img, t_object *sprite, t_data *data)
{
	t_sdraw		draw;
	int			x;

	calculate_transform(sprite, &data->player, &draw);
	calculate_dimensions(data, &draw);
	draw.texture = &data->textures.sprite;
	x = draw.start.x;
	while (x < draw.end.x)
	{
		draw.tex.x = (int)(256 * (x - (-draw.size.x / 2 + draw.screen_x)) *
			draw.texture->width / draw.size.x) / 256;
		if (draw.transform.y > 0 && x > 0 && x < data->map.resolution.x &&
				draw.transform.y < data->raycaster.dist_buffer[x])
			draw_sprite_column(img, &draw, x, data);
		x++;
	}
}

/*
**	This function draws a single column of a sprite.
*/

void		draw_sprite_column(t_img *img, t_sdraw *draw, int x, t_data *data)
{
	int				y;
	int				d;
	unsigned int	color;

	y = draw->start.y;
	while (y < draw->end.y)
	{
		d = y * 256 - data->map.resolution.y * 128 + draw->size.y * 128;
		draw->tex.y = ((d * draw->texture->height) / draw->size.y) / 256;
		color = get_pixel(&draw->texture->img, draw->tex.x, draw->tex.y);
		if (color != 0)
			draw_pixel(img, x, y, color);
		y++;
	}
}
