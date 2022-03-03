/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dvector_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 14:06:25 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:27:09 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
**	This function will add 2 double vectors.
*/

void	add_dvectors(t_dvector *dst, t_dvector *s1, t_dvector *s2)
{
	dst->x = s1->x + s2->x;
	dst->y = s1->y + s2->y;
}

/*
**	This function will subtract double vector s2 from s1.
*/

void	sub_dvectors(t_dvector *dst, t_dvector *s1, t_dvector *s2)
{
	dst->x = s1->x - s2->x;
	dst->y = s1->y - s2->y;
}

/*
**	This function will multiply a double vector by a double.
*/

void	multiply_dvector(t_dvector *dst, t_dvector *s1, double number)
{
	dst->x = s1->x * number;
	dst->y = s1->y * number;
}

/*
**	This function will rotate a double vector.
*/

void	rotate_dvector(t_dvector *vector, double rotation)
{
	double	orig_x;

	orig_x = vector->x;
	vector->x = orig_x * cos(rotation) - vector->y * sin(rotation);
	vector->y = orig_x * sin(rotation) + vector->y * cos(rotation);
}
