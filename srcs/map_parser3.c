/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 11:04:06 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 11:43:13 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <libft.h>

/*
**	This function will check a single line for a player spawn, and replace
**	it with an empty tile.
*/

void	check_line_for_spawn(char *line, int height, t_player *player)
{
	int		i;

	i = 0;
	while (*(line + i) != '\0')
	{
		if (ft_strchr("NESW", *(line + i)) != NULL)
		{
			if (player->pos.x != 0 || player->pos.y != 0)
				report_error("Multiple player spawns detected.", NULL);
			player->pos.x = (float)i + 0.5;
			player->pos.y = (float)height + 0.5;
			set_initial_dir(&player->dir, *(line + i));
			*(line + i) = '0';
		}
		i++;
	}
}

/*
**	This function will read the latest line being added to the map, and check
**	it for sprites.
*/

void	check_line_for_sprites(char *line, int height, t_data *data)
{
	int			i;
	double		x;
	double		y;
	t_texture	*sprite;
	t_object	*obj;

	sprite = &data->textures.sprite;
	i = 0;
	while (*(line + i) != '\0')
	{
		if (*(line + i) == '2')
		{
			x = i + 0.5;
			y = height + 0.5;
			obj = create_object(x, y, sprite);
			if (obj == NULL)
				report_error("A malloc failed.", data);
			insert_object_in_struct(data, obj);
		}
		i++;
	}
}

/*
**	This function will set the player's starting direction.
*/

void	set_initial_dir(t_dvector *dir, char direction)
{
	if (direction == 'N')
	{
		dir->x = 0;
		dir->y = -1;
	}
	else if (direction == 'E')
	{
		dir->x = 1;
		dir->y = 0;
	}
	else if (direction == 'S')
	{
		dir->x = 0;
		dir->y = 1;
	}
	else if (direction == 'W')
	{
		dir->x = -1;
		dir->y = 0;
	}
}

/*
**	This function replaces spaces from the map with 0.
*/

void	replace_spaces_in_map(char *row)
{
	while (*row != '\0')
	{
		if (*row == ' ')
			*row = '0';
		row++;
	}
}

/*
**	This function checks if a string if a valid color format.
**	That means 3 values from 0 to 255 separated by spaces.
*/

int		is_rgb_value(char *line)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (*line < '0' || *line > '9')
			return (0);
		while (*line >= '0' && *line <= '9')
			line++;
		if (*line == ',' && i != 2)
			line++;
		if (i == 2 && *line != '\0')
			return (0);
		i++;
	}
	return (1);
}
