/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 08:58:44 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/09 08:15:01 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

/*
**	Main function. Clean the struct, read the map (if given), and set up
**	MLX and the hooks.
*/

int			main(int argc, char **argv)
{
	t_data	data;

	data.bitmap_mode = check_arguments(argc, argv);
	clean_data_struct(&data);
	parse_map_file(*(argv + 1), &data);
	validate_map(&data);
	init_camera(&data.player);
	mlx_setup(&data);
	init_textures(&data, &data.textures);
	draw_frame(&data);
	if (data.bitmap_mode == 1)
		make_bitmap(&data);
	else
	{
		mlx_set_hooks(&data);
		mlx_loop(data.mlx);
	}
	return (0);
}

/*
**	This function will set up MLX, create the window and 2 images. Closes
**	cleanly if any call to MLX fails. If bitmap is 1, only 1 image and no
**	window will be created.
*/

void		mlx_setup(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		report_error("Something went wrong while setting up MLX.", data);
	init_dist_buffer(data, data->map.resolution.x);
	if (data->bitmap_mode == 0)
		resize_screen(data);
	data->img1.img = mlx_new_image(data->mlx, data->map.resolution.x,
			data->map.resolution.y);
	if (data->img1.img == NULL)
		report_error("Something went wrong while setting up MLX.", data);
	data->img1.addr = mlx_get_data_addr(data->img1.img, &data->img1.bpp,
			&data->img1.line_length, &data->img1.endian);
	if (data->bitmap_mode == 1)
		return ;
	data->window = mlx_new_window(data->mlx, data->map.resolution.x,
			data->map.resolution.y, "cub3D");
	if (data->window == NULL)
		report_error("Something went wrong while setting up MLX.", data);
	data->img2.img = mlx_new_image(data->mlx, data->map.resolution.x,
			data->map.resolution.y);
	if (data->img2.img == NULL)
		report_error("Something went wrong while setting up MLX.", data);
	data->img2.addr = mlx_get_data_addr(data->img2.img, &data->img2.bpp,
			&data->img2.line_length, &data->img2.endian);
}

/*
**	This function will set up the hooks that the program will need to detect
**	certain events, like keyboard interaction, clicking the close button, etc.
*/

void		mlx_set_hooks(t_data *data)
{
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_hook(data->window, KEY_PRESS, KEY_PRESS_MASK, &key_press, data);
	mlx_hook(data->window, KEY_RELEASE, KEY_RELEASE_MASK, &key_release, data);
	mlx_hook(data->window, DESTROY_EVENT, STRUCTURE_MASK, &close_game, data);
	mlx_loop_hook(data->mlx, &loop_game, data);
}

/*
**	This function will check if the correct amount of arguments is given, and
**	if the map is of the .cub type. Gives an error if something is wrong.
**	Returns 1 if the argument --save is provided.
*/

int			check_arguments(int argc, char **argv)
{
	if (argc == 1)
		report_error("No map given as argument.", NULL);
	if (argc > 3)
		report_error("Too many arguments.", NULL);
	if (check_file_extension(*(argv + 1), ".cub") == 0)
		report_error("Argument is not a .cub file", NULL);
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		report_error("Second argument needs to be --save or nothing.", NULL);
	if (argc == 3)
		return (1);
	return (0);
}

/*
**	This function will resize the resolution given if it greater than the
**	current screen resolution.
*/

void		resize_screen(t_data *data)
{
	int		max_x;
	int		max_y;

	mlx_get_screen_size(data->mlx, &max_x, &max_y);
	if (data->map.resolution.x > max_x)
		data->map.resolution.x = max_x;
	if (data->map.resolution.y > max_y - 45)
		data->map.resolution.y = max_y - 45;
}
