/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 09:05:24 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:27:41 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
**	This is to copy the info from the map file into a 2-dimensional array.
*/

void	create_temp_row(t_map *map, char *new_row)
{
	int		i;
	char	**new_map;

	i = 0;
	while (*(map->tiles + i) != NULL)
		i++;
	new_map = malloc(sizeof(char*) * (i + 2));
	if (new_map == NULL)
	{
		free_string_array(map->tiles);
		report_error("A malloc failed.", NULL);
	}
	i = 0;
	while (*(map->tiles + i) != NULL)
	{
		*(new_map + i) = *(map->tiles + i);
		i++;
	}
	*(new_map + i) = new_row;
	*(new_map + i + 1) = NULL;
	free(map->tiles);
	map->tiles = new_map;
}

/*
**	This function will create a 2d-array with the dimensions of the existing
**	map to be used for the map-check algorithm. Will be filled with 0 at
**	first.
*/

char	**create_visited_map(t_data *data)
{
	int		i;
	char	**new_map;

	new_map = malloc(sizeof(char*) * (data->map.size.y + 1));
	if (new_map == NULL)
		report_error("A malloc failed.", data);
	i = 0;
	while (i < data->map.size.y)
	{
		*(new_map + i) = malloc(data->map.size.x + 1);
		if (*(new_map + i) == NULL)
		{
			free_string_array(new_map);
			report_error("A malloc failed.", data);
		}
		ft_memset(*(new_map + i), '0', data->map.size.x);
		*(*(new_map + i) + data->map.size.x) = '\0';
		i++;
	}
	*(new_map + i) = NULL;
	return (new_map);
}

/*
**	This function will be called if the map isn't square, it will pad the
**	lines with '0' to square it.
*/

void	square_map(t_data *data, int length)
{
	char	*padded_line;
	int		i;
	int		old_length;

	i = 0;
	while (*(data->map.tiles + i) != NULL)
	{
		if ((int)ft_strlen(*(data->map.tiles + i)) != length)
		{
			padded_line = malloc(length + 1);
			if (padded_line == NULL)
				report_error("A malloc failed.", data);
			old_length = (int)ft_strlen(*(data->map.tiles + i));
			ft_memcpy(padded_line, *(data->map.tiles + i), old_length);
			while (old_length < length)
			{
				*(padded_line + old_length) = '0';
				old_length++;
			}
			*(padded_line + old_length) = '\0';
			free(*(data->map.tiles + i));
			*(data->map.tiles + i) = padded_line;
		}
		i++;
	}
}

/*
**	Quick helper function to make an empty 2-dimensional character array for
**	the tileset.
*/

char	**make_empty_tileset(void)
{
	char **result;

	result = malloc(sizeof(char*));
	if (result == NULL)
		return (NULL);
	*result = NULL;
	return (result);
}

/*
**	This function checks the map for illegal elements and returns 1 if it finds
**	any. 0 otherwise.
*/

int		check_illegal_map_elements(char *row)
{
	while (*row != '\0')
	{
		if (ft_strchr("012NSWE", *row) == NULL)
			return (1);
		row++;
	}
	return (0);
}
