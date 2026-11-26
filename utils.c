/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 19:26:55 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/26 19:18:47 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	degrees_to_rad(double degrees)
{
	return (degrees * PI / 180);
}

t_bool	wall_check(int grid_coords[2], char **map)
{
	if (map[grid_coords[Y]][grid_coords[X]] == '1')
		return (TRUE);
	return (FALSE);
}
