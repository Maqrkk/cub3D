/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 15:44:48 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:29:29 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <mlx.h>
#include <libft.h>

/*
**	This function will free an array of strings, most likely allocated by
**	ft_split.
*/

void		free_string_array(char **array)
{
	int		i;

	i = 0;
	while (*(array + i) != NULL)
	{
		free(*(array + i));
		i++;
	}
	free(array);
}

/*
**	This function will return the image that is not currently on the screen.
*/

t_img		*get_new_image(t_data *data)
{
	if (data->active_image == 1)
		return (&data->img2);
	return (&data->img1);
}

/*
**	This function will put the new image to the window, and set the
**	active_image variable accordingly.
*/

void		set_new_image(t_data *data)
{
	t_img	*new_image;

	data->active_image = (data->active_image == 2) ? 1 : 2;
	if (data->active_image == 1)
		new_image = &data->img1;
	else
		new_image = &data->img2;
	mlx_put_image_to_window(data->mlx, data->window, new_image->img, 0, 0);
}

/*
**	This function will compare the file name with the extension. Returns
**	1 if correct, 0 if not.
*/

int			check_file_extension(char *file, char *extension)
{
	int		ext_len;
	int		file_len;
	int		i;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (ext_len >= file_len)
		return (0);
	i = 1;
	while (i <= ext_len)
	{
		if (file[file_len - i] != extension[ext_len - i])
			return (0);
		i++;
	}
	return (1);
}
