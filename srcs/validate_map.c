/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:26:19 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:58:22 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
**	This function will first check if all the necessary values are set, then
**	call a function to test if the map is 'closed'. Returns 1 if everything
**	is ok, 0 if there is something missing or wrong.
*/

int		validate_map(t_data *data)
{
	char		**visited_fields;
	int			map_closed;
	t_dvector	*player;

	check_values_set(data);
	check_textures(data);
	visited_fields = create_visited_map(data);
	player = &data->player.pos;
	if (player->x == 0)
		report_error("No player in the map.", data);
	map_closed = test_position_valid(&data->map, visited_fields,
			(int)(player->x - 0.5), (int)(player->y - 0.5));
	free_string_array(visited_fields);
	if (map_closed == -1)
		report_error("The map isn't closed properly.", data);
	return (1);
}

/*
**	This function will check if all the necessary values have been set,
**	and give error messages if not.
*/

void	check_values_set(t_data *data)
{
	if (data->map.resolution.x == 0 || data->map.resolution.y == 0)
		report_error("Resolution not set.", data);
	if (data->map.parser.floor_set == 0)
		report_error("Floor color not set.", data);
	if (data->map.parser.ceiling_set == 0)
		report_error("Ceiling color not set.", data);
	if (data->textures.north.file == NULL)
		report_error("North texture not set.", data);
	if (data->textures.east.file == NULL)
		report_error("East texture not set.", data);
	if (data->textures.south.file == NULL)
		report_error("South texture not set.", data);
	if (data->textures.west.file == NULL)
		report_error("West texture not set.", data);
	if (data->textures.sprite.file == NULL)
		report_error("Sprite texture not set.", data);
}

/*
**	This function will recursively loop through all positions that are
**	reachable from the starting point. Will return a negative number
**	if the outside of the map can be reached, 0 otherwise.
*/

int		test_position_valid(t_map *map, char **visited, int x, int y)
{
	if (x < 0 || x > map->size.x - 1 || y < 0 ||
			y > map->size.y - 1)
		return (-1);
	if (map->tiles[y][x] == '1' || visited[y][x] == '1')
		return (0);
	visited[y][x] = '1';
	if (test_position_valid(map, visited, x - 1, y - 1) == -1)
		return (-1);
	if (test_position_valid(map, visited, x, y - 1))
		return (-1);
	if (test_position_valid(map, visited, x + 1, y - 1))
		return (-1);
	if (test_position_valid(map, visited, x - 1, y))
		return (-1);
	if (test_position_valid(map, visited, x + 1, y))
		return (-1);
	if (test_position_valid(map, visited, x - 1, y + 1))
		return (-1);
	if (test_position_valid(map, visited, x, y + 1))
		return (-1);
	if (test_position_valid(map, visited, x + 1, y + 1))
		return (-1);
	return (0);
}

/*
**	This function will test if the textures are valid files.
*/

void	check_textures(t_data *data)
{
	int			fd;
	int			i;
	t_texture	*texture;
	char		*filename;

	i = 0;
	while (i < 5)
	{
		texture = get_texture_by_id(&data->textures, i);
		filename = texture->file;
		if (is_image_file(filename) == 0)
			report_error_param(filename, "is not the right format.", data);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			report_error_param(filename, "failed to open.", data);
		close(fd);
		i++;
	}
}
