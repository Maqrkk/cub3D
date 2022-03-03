/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 15:55:53 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:08:16 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Main function to parse the map. Uses the get_next_line project to read
**	line by line, and parses them with parse_line.
*/

void	parse_map_file(char *file, t_data *data)
{
	int		gnl_return;
	t_map	*map;

	map = &data->map;
	map->parser.fd = open(file, O_RDONLY);
	if (map->parser.fd == -1)
		report_error("Something went wrong while opening the file.", data);
	gnl_return = 1;
	while (gnl_return > 0)
	{
		gnl_return = get_next_line(map->parser.fd, &map->parser.line);
		if (gnl_return == -1)
			report_error("Something went wrong while reading the file.", data);
		parse_line(map->parser.line, data);
		free(map->parser.line);
	}
	close(map->parser.fd);
	map->parser.fd = 0;
	map->parser.line = NULL;
	if (!ft_array_is_square(data->map.tiles))
		square_map(data, data->map.size.x);
}

/*
**	This function will process the lines from the file, and re-route it to
**	the correct sub-parser.
*/

void	parse_line(char *line, t_data *data)
{
	int		type;
	t_map	*map;

	map = &data->map;
	if (map->parser.phase == 2 && *line != '\0')
		report_error("Map format is wrong, the map has to be last.", data);
	if (map->parser.phase == 1 && *line == '\0')
		map->parser.phase = 2;
	if (*line == '\0')
		return ;
	type = line_type(line);
	if (type == 0)
		report_error("Incorrect character found in map file.", data);
	if (map->parser.phase == 1 && type == 1)
		report_error("Map format is wrong, the map has to be last.", data);
	else if (type == 1)
		parse_element_line(line, data);
	else
	{
		map->parser.phase = 1;
		parse_map_line(line, data);
	}
}

/*
**	This function will process single lines from our .cub file for elements,
**	like resolution, color or sprites. Uses split to get rid of all
**	space separators.
*/

void	parse_element_line(char *line, t_data *data)
{
	int		type;

	type = check_valid_map_element(line, data);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (type == 1 || type == 2)
		parse_plane(line, data, &data->map, type);
	else if (type == 8)
		parse_resolution(line, data);
	else
		parse_sprite(line, &data->textures, data, type);
}

/*
**	This function will process single lines from the .cub file and parse it
**	for map info.
*/

void	parse_map_line(char *line, t_data *data)
{
	char		*new_row;
	t_map		*map;
	t_player	*player;

	map = &data->map;
	player = &data->player;
	new_row = ft_strdup(line);
	if (new_row == NULL)
		report_error("A malloc failed.", data);
	replace_spaces_in_map(new_row);
	if (check_illegal_map_elements(new_row) == 1)
		report_error("Illegal character found in map.", data);
	check_line_for_spawn(new_row, map->size.y, player);
	check_line_for_sprites(new_row, map->size.y, data);
	create_temp_row(map, new_row);
	if ((int)ft_strlen(new_row) > map->size.x)
		map->size.x = ft_strlen(new_row);
	map->size.y++;
}

/*
**	This function will look at the line and return 1 for an element, 2 for map
**	or 0 for something else.
*/

int		line_type(char *line)
{
	if (ft_strchr("CEFNSRW", *line) != NULL)
		return (1);
	else if ((*line >= '0' && *line <= '9') || *line == ' ')
		return (2);
	return (0);
}
