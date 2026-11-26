/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:34:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/26 14:56:54 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_bool	is_inside_the_map(int grid_coords[2], t_map_res *map_res,
	double intersection[2])
{
	if (grid_coords[Y] < 0 || grid_coords[Y] >= map_res->nbr_of_rows
		|| grid_coords[X] < 0
		|| grid_coords[X] >= (int)map_res->size_of_longest_row
		|| map_res->map[grid_coords[Y]][grid_coords[X]] == ' ')
	{
		intersection[X] = INT_MAX;
		intersection[Y] = INT_MAX;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	wall_check(int grid_coords[2], t_map_res *map_res)
{
	if (map_res->map[grid_coords[Y]][grid_coords[X]] == '1')
		return (TRUE);
	return (FALSE);
}
