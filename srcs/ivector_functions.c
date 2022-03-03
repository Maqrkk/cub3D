/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 14:02:21 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:27:32 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	This function will add 2 int vectors.
*/

void	add_ivectors(t_ivector *dst, t_ivector *s1, t_ivector *s2)
{
	dst->x = s1->x + s2->x;
	dst->y = s1->y + s2->y;
}

/*
**	This function will subtract int vector s2 from s1.
*/

void	sub_ivectors(t_ivector *dst, t_ivector *s1, t_ivector *s2)
{
	dst->x = s1->x - s2->x;
	dst->y = s1->y - s2->y;
}

/*
**	This function will multiplty an int vector by a number.
*/

void	multiply_ivector(t_ivector *dst, t_ivector *s1, int number)
{
	dst->x = s1->x * number;
	dst->y = s1->y * number;
}
