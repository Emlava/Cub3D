/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:34:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/13 16:53:17 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_bool	is_inside_the_map(int grid_x, int grid_y, t_map_res *map_res,
	int intersection[2])
{
	if (grid_y < 0 || grid_y >= map_res->nbr_of_rows || grid_x < 0
		|| grid_x >= (int)map_res->size_of_longest_row
		|| map_res->map[grid_y][grid_x] == ' ')
	{
		intersection[X] = INT_MAX;
		intersection[Y] = INT_MAX;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	wall_check(int grid_x, int grid_y, t_map_res *map_res)
{
	if (map_res->map[grid_y][grid_x] == '1')
		return (TRUE);
	return (FALSE);
}
