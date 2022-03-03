/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser2_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 13:53:40 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:56:07 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <libft.h>

/*
**	Quick helper function to parse the first element of a line and see if it
**	is a valid element.
*/

int		check_valid_map_element(char *line, t_data *data)
{
	if (*line == 'F' && *(line + 1) == ' ')
		return (1);
	if (*line == 'C' && *(line + 1) == ' ')
		return (2);
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (3);
	if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		return (4);
	if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (5);
	if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		return (6);
	if (*line == 'S' && *(line + 1) == ' ')
		return (7);
	if (*line == 'R' && *(line + 1) == ' ')
		return (8);
	report_error("Found a wrong element in the map file.", data);
	return (0);
}

/*
**	This function will try to read a valid color from the elements given and
**	put it in the map struct.
*/

void	parse_plane(char *line, t_data *data, t_map *map, int type)
{
	int		color;

	if (type == 1 && map->parser.floor_set == 1)
		report_error("Floor set twice.", data);
	if (type == 2 && map->parser.ceiling_set == 1)
		report_error("Ceiling set twice.", data);
	if (is_rgb_value(line) == 0)
		parse_sprite(line, &data->textures, data, type);
	else
	{
		color = read_color(line, data);
		if (type == 1)
			map->floor_color = color;
		else
			map->ceil_color = color;
	}
	if (type == 1)
		map->parser.floor_set = 1;
	else
		map->parser.ceiling_set = 1;
}

/*
**	This function will try to read the resolution and put it in the map
**	struct.
*/

void	parse_resolution(char *line, t_data *data)
{
	int		i;
	int		*dim;

	if (data->map.resolution.x != 0)
		report_error("Resolution was given twice.", data);
	i = 0;
	while (i < 2)
	{
		if (ft_isnumber(line) == 0)
			report_error("Argument for resolution has to be a number.", data);
		dim = (i == 0) ? &data->map.resolution.x : &data->map.resolution.y;
		*dim = ft_atoi(line);
		while (*line >= '0' && *line <= '9')
			line++;
		if (i == 0)
			while (*line == ' ')
				line++;
		if (i == 1 && *line != '\0')
			report_error("Incorrect format for resolution.", data);
		i++;
	}
}

/*
**	This function will try to read a path to a sprite, and put it in the map
**	struct for the relevant sprite.
*/

void	parse_sprite(char *line, t_textures *textures, t_data *data, int type)
{
	char	*sprite;

	sprite = ft_strdup(line);
	if (sprite == NULL)
		report_error("A malloc failed.", data);
	if (type == 3 && textures->north.file == NULL)
		textures->north.file = sprite;
	else if (type == 4 && textures->east.file == NULL)
		textures->east.file = sprite;
	else if (type == 5 && textures->south.file == NULL)
		textures->south.file = sprite;
	else if (type == 6 && textures->west.file == NULL)
		textures->west.file = sprite;
	else if (type == 7 && textures->sprite.file == NULL)
		textures->sprite.file = sprite;
	else if (type == 1 && textures->floor.file == NULL)
		textures->floor.file = sprite;
	else if (type == 2 && textures->ceiling.file == NULL)
		textures->ceiling.file = sprite;
	else
		report_error("A sprite was given a value twice.", data);
}

/*
**	This function will get a comma-separated string from the map file and
**	convert it to an int.
*/

int		read_color(char *s, t_data *data)
{
	int		values;
	int		tmp;
	int		color;

	values = 0;
	color = 0;
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			report_error("Color incorrectly formatted.", data);
		tmp = ft_atoi(s);
		if (tmp > 255)
			report_error("Color value cannot be higher than 255.", data);
		color = (color << 8) + tmp;
		values++;
		while (*s >= '0' && *s <= '9')
			s++;
		if ((*s != ',' && *s != '\0') || (*s == ',' && values == 3))
			report_error("Color incorrectly formatted.", data);
		if (*s == ',')
			s++;
	}
	if (values != 3)
		report_error("Color incorrectly formatted.", data);
	return (color);
}
