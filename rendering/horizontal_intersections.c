/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 14:03:24 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/16 20:26:50 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	find_nearest_intersection(int curr_intersection[2],
	t_player_res *player, double ray_angle_in_rad)
{
	curr_intersection[Y] = (int)(player->coords[Y] / WORLD_SIDE_LENGTH)
		* WORLD_SIDE_LENGTH;
	if (player->ray_angle < 180) // Facing up
			curr_intersection[Y] -= 1;
	else // Facing down
			curr_intersection[Y] += WORLD_SIDE_LENGTH;
	curr_intersection[X] = player->coords[X]
	+ round((player->coords[Y] - curr_intersection[Y]) / tan(ray_angle_in_rad));
	return ;
}

static void	determine_steps(int *x_step, int *y_step, double ray_angle,
	double ray_angle_in_rad)
{
	*x_step = WORLD_SIDE_LENGTH / tan(ray_angle_in_rad);
	if (ray_angle > 90 && ray_angle < 270) // Facing left
		*x_step = -(*x_step);
	*y_step = WORLD_SIDE_LENGTH;
	if (ray_angle < 180)
		*y_step = -(*y_step);
	return ;
}

void	check_horizontal_intersections(t_player_res *player, t_map_res *map_res,
	int curr_intersection[2])
{
	double	ray_angle_in_rad;
	int		grid_coords[2];
	int		x_step;
	int		y_step;

	// Avoid a tan of 0, which would lead to a division by 0
	if (player->ray_angle == 0 || player->ray_angle == 180)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	ray_angle_in_rad = (player->ray_angle * PI) / 180;
	find_nearest_intersection(curr_intersection, player,
		ray_angle_in_rad);
	grid_coords[X] = curr_intersection[X] / WORLD_SIDE_LENGTH;
	grid_coords[Y] = curr_intersection[Y] / WORLD_SIDE_LENGTH;

	if (is_inside_the_map(grid_coords, map_res, curr_intersection)
		&& !wall_check(grid_coords, map_res))
	{
		determine_steps(&x_step, &y_step, player->ray_angle, ray_angle_in_rad);
		find_wall(curr_intersection, x_step, y_step, map_res);
	}
	return ;
}
