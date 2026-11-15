/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:34:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/15 14:41:20 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_bool	is_inside_the_map(int grid_coords[2], t_map_res *map_res,
	int intersection[2])
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

void	find_wall(int curr_intersection[2], int x_step, int y_step,
	t_map_res *map_res)
{
	int	grid_coords[2];

	curr_intersection[X] += x_step;
	curr_intersection[Y] += y_step;
	grid_coords[X] = curr_intersection[X] / WORLD_SIDE_LENGTH;
	grid_coords[Y] = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	while (is_inside_the_map(grid_coords, map_res, curr_intersection)
		&& !wall_check(grid_coords, map_res))
	{
		curr_intersection[X] += x_step;
		curr_intersection[Y] += y_step;
		grid_coords[X] = curr_intersection[X] / WORLD_SIDE_LENGTH;
		grid_coords[Y] = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	}
	return ;
}
