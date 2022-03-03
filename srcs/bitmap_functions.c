/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 12:57:33 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:26:43 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

/*
**	Main function for creating the bitmap.
*/

void		make_bitmap(t_data *data)
{
	int		line_size;
	int		total_size;
	int		i;

	line_size = data->map.resolution.x * 3;
	if (line_size % 4 != 0)
		line_size += 4 - (data->map.resolution.x * 3) % 4;
	total_size = line_size * data->map.resolution.y + 54;
	data->bitmap_fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->bitmap_fd == -1)
		report_error("Creating the screenshot failed.", data);
	write_bitmap_header(total_size, data);
	i = data->map.resolution.y - 1;
	while (i >= 0)
	{
		write_horizontal_line(data->bitmap_fd, data, i, line_size);
		i--;
	}
	close_game(data);
}

/*
**	This function will create the header for the bitmap image.
*/

void		write_bitmap_header(int file_size, t_data *data)
{
	char	*buffer;
	int		ret;

	buffer = malloc(54);
	if (buffer == NULL)
		report_error("A malloc failed.", data);
	ft_bzero(buffer, 54);
	buffer[0] = 'B';
	buffer[1] = 'M';
	*(int *)(buffer + 2) = file_size;
	*(int *)(buffer + 10) = 54;
	*(int *)(buffer + 14) = 40;
	*(int *)(buffer + 18) = data->map.resolution.x;
	*(int *)(buffer + 22) = data->map.resolution.y;
	*(short *)(buffer + 26) = 1;
	*(short *)(buffer + 28) = 24;
	ret = write(data->bitmap_fd, buffer, 54);
	free(buffer);
	if (ret == -1)
		report_error("A write failed.", data);
}

/*
**	This function writes a horizontal line from an image to a file.
*/

void		write_horizontal_line(int fd, t_data *data, int y, int size)
{
	unsigned int	color;
	int				x;
	t_img			*img;
	int				ret;

	img = get_new_image(data);
	x = 0;
	while (x < data->map.resolution.x)
	{
		color = get_pixel(img, x, y);
		ret = write(fd, &color, 3);
		if (ret == -1)
			report_error("A write failed.", data);
		size -= 3;
		x++;
	}
	if (size > 0)
	{
		ret = write(fd, "\0\0\0", size);
		if (ret == -1)
			report_error("A write failed.", data);
	}
}
