/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:08:44 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 13:45:53 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_structs.h"

/*
**	bitmap_functions.c
*/

void			make_bitmap(t_data *data);
void			write_bitmap_header(int file_size, t_data *data);
void			write_horizontal_line(int fd, t_data *data, int y, int size);

/*
**	close_game.c
*/

int				close_game(t_data *data);
void			destroy_textures(t_data *data, t_textures *textures);
void			destroy_objects(t_data *data);

/*
**	cub3d.c
*/

int				main(int argc, char **argv);
void			mlx_setup(t_data *data);
void			mlx_set_hooks(t_data *data);
int				check_arguments(int argc, char **argv);
void			resize_screen(t_data *data);

/*
**	draw_functions1.c
*/

void			draw_frame(t_data *data);
void			draw_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_img *img, int x, int y);
void			draw_column(t_img *img, t_data *data, int x, int height);
void			draw_wall(t_img *img, t_draw *draw, double wall_x);

/*
**	draw_functions2.c
*/

void			draw_planes_simple(t_img *img, t_map *map);
void			draw_planes(t_img *img, t_data *data);
void			draw_sprites(t_img *img, t_data *data);
void			draw_single_sprite(t_img *img, t_object *sprite, t_data *data);
void			draw_sprite_column(t_img *img, t_sdraw *draw, int x,
					t_data *data);

/*
**	sprite_functions.c
*/

void			calculate_transform(t_object *sprite, t_player *player,
					t_sdraw *draw);
void			calculate_dimensions(t_data *data, t_sdraw *draw);

/*
**	dvector_functions.c
*/

void			add_dvectors(t_dvector *dst, t_dvector *s1, t_dvector *s2);
void			sub_dvectors(t_dvector *dst, t_dvector *s1, t_dvector *s2);
void			multiply_dvector(t_dvector *dst, t_dvector *s1, double number);
void			rotate_dvector(t_dvector *vector, double rotation);

/*
**	hook_functions.c
*/

int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				loop_game(t_data *data);

/*
**	ivector_functions.c
*/

void			add_ivectors(t_ivector *dst, t_ivector *s1, t_ivector *s2);
void			sub_ivectors(t_ivector *dst, t_ivector *s1, t_ivector *s2);
void			multiply_ivector(t_ivector *dst, t_ivector *s1, int number);

/*
**	map_functions.c
*/

void			create_temp_row(t_map *map, char *tiles);
char			**create_visited_map(t_data *data);
void			square_map(t_data *data, int length);
char			**make_empty_tileset(void);
int				check_illegal_map_elements(char *row);

/*
**	map_parser1.c
*/

void			parse_map_file(char *file, t_data *data);
void			parse_line(char *line, t_data *data);
void			parse_element_line(char *line, t_data *data);
void			parse_map_line(char *line, t_data *data);
int				line_type(char *line);

/*
**	map_parser2.c
*/

int				check_valid_map_element(char *line, t_data *data);
void			parse_plane(char *line, t_data *data, t_map *map, int type);
void			parse_resolution(char *line, t_data *data);
void			parse_sprite(char *line, t_textures *textures, t_data *data,
					int type);
int				read_color(char *s, t_data *data);

/*
**	map_parser3.c
*/

void			check_line_for_spawn(char *line, int height, t_player *player);
void			check_line_for_sprites(char *line, int height, t_data *data);
void			set_initial_dir(t_dvector *dir, char direction);
void			replace_spaces_in_map(char *row);
int				is_rgb_value(char *line);

/*
**	move_player.c
*/

int				move_player(t_data *data);
void			rotate_player(t_player *player, double rotation);
void			move_forward_or_backward(t_data *data, int direction);
void			move_sideways(t_data *data, int direction);
void			get_movement(t_ivector *movement, double *rotation,
					t_keystate *keys);

/*
**	object_functions.c
*/

t_object		*create_object(double x, double y, t_texture *sprite);
void			insert_object_in_struct(t_data *data, t_object *new);

/*
**	raycaster1.c
*/

void			cast_ray(int column, t_data *data);
void			init_camera(t_player *player);
void			prepare_raycaster(t_data *data, int column);
void			set_direction_variables(t_raycast *rc, t_player *player);
void			find_wall_hit(t_data *data);

/*
**	raycaster2.c
*/

void			calculate_distance(t_raycast *rc, t_player *player,
					int column);
void			find_wall_x(t_data *data);
/*
**	report_error.c
*/

void			report_error(char *message, t_data *data);
void			report_error_param(char *param, char *message, t_data *data);

/*
**	struct_functions.c
*/

void			clean_data_struct(t_data *data);
void			clean_map_struct(t_map *map);
void			clean_raycaster_struct(t_raycast *rc);
void			clean_textures_struct(t_textures *textures);
void			clean_player_struct(t_player *player);

/*
**	texture_functions.c
*/

t_texture		*get_texture_for_wall(t_data *data);
void			init_textures(t_data *data, t_textures *textures);
void			init_texture(t_data *data, t_texture *tex);
t_texture		*get_texture_by_id(t_textures *textures, int id);

/*
**	utilities1.c
*/

void			free_string_array(char **array);
t_img			*get_new_image(t_data *data);
void			set_new_image(t_data *data);
int				check_file_extension(char *file, char *extension);

/*
**	utilities2.c
*/

int				is_image_file(char *file);
void			init_dist_buffer(t_data *data, int size);
void			calculate_sprite_distances(t_objects *objects,
					t_player *player);
void			sort_sprites(t_objects *objects);

/*
**	validate_map.c
*/

int				validate_map(t_data *data);
void			check_values_set(t_data *data);
int				test_position_valid(t_map *map, char **visited, int x, int y);
void			check_textures(t_data *data);

#endif
