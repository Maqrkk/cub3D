/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 09:16:02 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 16:02:55 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

/*
**	Defines for all the keys.
*/

# define KEY_ESCAPE 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

/*
**	Defines for all events used in the project.
*/

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define MOUSE_MOVE 6
# define DESTROY_EVENT 17

/*
**	Defines for masks to go with the events.
*/

# define KEY_PRESS_MASK 1L<<0
# define KEY_RELEASE_MASK 1L<<1
# define MOUSE_MOVE_MASK 1L<<6
# define STRUCTURE_MASK 1L<<17

/*
**	Struct for map parsing.
*/

typedef struct	s_parser
{
	int			fd;
	int			phase;
	char		*line;
	int			floor_set;
	int			ceiling_set;
}				t_parser;

/*
**	Struct for image data.
**	addr is the actual address of the first pixel.
**	bpp is the bits_per_pixel for this image.
**	line_length is the total length of a single line.
*/

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

/*
**	Struct for a single texture.
*/

typedef struct	s_texture
{
	char		*file;
	t_img		img;
	int			width;
	int			height;
}				t_texture;

/*
**	Struct for all textures needed by the program.
*/

typedef struct	s_textures
{
	t_texture	north;
	t_texture	east;
	t_texture	south;
	t_texture	west;
	t_texture	sprite;
	t_texture	floor;
	t_texture	ceiling;
}				t_textures;

/*
**	Struct for keystates.
**	These will be set to 1 for on, 0 for off.
*/

typedef struct	s_keystate
{
	int			left;
	int			right;
	int			w;
	int			a;
	int			s;
	int			d;
	int			mouse_rotation;
}				t_keystate;

/*
**	Struct for a double vector.
*/

typedef struct	s_dvector
{
	double		x;
	double		y;
}				t_dvector;

/*
**	Struct for an int vector.
*/

typedef struct	s_ivector
{
	int			x;
	int			y;
}				t_ivector;

/*
**	Struct for an object in the game.
*/

typedef struct	s_object
{
	t_dvector	pos;
	t_texture	*sprite;
	double		dist;
	int			solid;
	int			pickup;
}				t_object;

/*
**	Struct for all objects in the map.
*/

typedef struct	s_objects
{
	int			amount;
	t_object	**objects;
}				t_objects;

/*
**	Struct for a map.
**	fd is the file descriptor for the map file.
**	tiles will be a multi-dimensional array of tile structs.
**	elements_done is a flag for the map reading process.
*/

typedef struct	s_map
{
	t_ivector	resolution;
	t_ivector	size;
	char		**tiles;
	int			floor_color;
	int			ceil_color;
	t_object	*sprites;
	t_parser	parser;
}				t_map;

/*
**	Struct for the player. Holds information about the location, direction
**	camera, movement and rotation speeds.
*/

typedef struct	s_player
{
	t_dvector	pos;
	t_ivector	map;
	t_dvector	dir;
	t_dvector	plane;
	double		move_speed;
	double		turn_speed;
}				t_player;

/*
**	Struct for a raycaster.
**	Holds all important values for raycasting.
*/

typedef struct	s_raycast
{
	double		camera_x;
	t_dvector	ray_dir;
	t_dvector	delta_dist;
	t_dvector	side_dist;
	t_ivector	step;
	int			hit;
	int			side;
	double		perp_dist;
	double		wall_x;
	double		*dist_buffer;

}				t_raycast;

/*
**	Struct with information about the column that's being drawn.
*/

typedef struct	s_draw
{
	int			x;
	int			tex_x;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	int			screen_height;
	t_texture	*texture;
}				t_draw;

/*
**	Struct with information about drawing a sprite.
*/

typedef struct	s_sdraw
{
	t_dvector	transform;
	int			screen_x;
	t_ivector	size;
	t_ivector	start;
	t_ivector	end;
	t_ivector	tex;
	t_texture	*texture;
}				t_sdraw;

/*
**	Struct with information about drawing planes (floor and ceiling).
*/

typedef struct	s_pdraw
{
	t_dvector	ray1;
	t_dvector	ray2;
	t_dvector	step;
	t_dvector	pos;
	t_ivector	cell;
	double		pos_z;
	double		row_distance;
}				t_pdraw;

/*
**	Struct to keep all important data together in 1 variable.
*/

typedef struct	s_data
{
	void		*mlx;
	void		*window;
	t_img		img1;
	t_img		img2;
	int			active_image;
	int			mouse_x;
	int			bitmap_mode;
	int			bitmap_fd;
	t_map		map;
	t_keystate	keystates;
	t_raycast	raycaster;
	t_player	player;
	t_objects	objects;
	t_textures	textures;
}				t_data;

#endif
