/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   report_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 13:50:34 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/03/06 09:28:46 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
**	This function will report an error, and free any allocated pointers
**	if necessary.
*/

void		report_error(char *message, t_data *data)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
	if (data != NULL)
		close_game(data);
	exit(1);
}

/*
**	This function reports an error with a parameter.
*/

void		report_error_param(char *param, char *message, t_data *data)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(param, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
	if (data != NULL)
		close_game(data);
	exit(1);
}
