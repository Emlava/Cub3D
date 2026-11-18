/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 14:43:01 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/18 18:55:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	find_nearest_intersection(double curr_intersection[2],
	t_player_res *player, double ray_angle_in_rad)
{
	curr_intersection[X] = (int)(player->coords[X] / WORLD_SIDE_LENGTH)
		* WORLD_SIDE_LENGTH;
	if (player->ray_angle < 90 || player->ray_angle > 270) // Facing right
		curr_intersection[X] += WORLD_SIDE_LENGTH;
	else // Facing left
		curr_intersection[X] -= 1;
	curr_intersection[Y] = player->coords[Y]
		+ round((player->coords[X] - curr_intersection[X]) * tan(ray_angle_in_rad));
	return ;
}

// cf. determine_steps from horizontal_intersections.c
static void	determine_steps(double *x_step, double *y_step, double ray_angle,
	double ray_angle_in_rad)
{
	*y_step = WORLD_SIDE_LENGTH * tan(ray_angle_in_rad);
	if (ray_angle > 90 && ray_angle < 270) // Facing left
		*x_step = -WORLD_SIDE_LENGTH;
	else
	 {
		*x_step = WORLD_SIDE_LENGTH;
		*y_step = -(*y_step);
	 }
	return ;
}

void	check_vertical_intersections(t_player_res *player, t_map_res *map_res,
	double curr_intersection[2])
{
	double	ray_angle_in_rad;
	int		grid_coords[2];
	double	x_step;
	double	y_step;
	
	// Manage a ray parallel to grid lines
	if (fabs(player->ray_angle - 90) < 0.0001
	|| fabs(player->ray_angle - 270) < 0.0001)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	ray_angle_in_rad = (player->ray_angle * PI) / 180;

	// Find the nearest intersection coordinates
	find_nearest_intersection(curr_intersection, player,
		ray_angle_in_rad);
	define_grid_coords(curr_intersection, grid_coords);
	
	if (is_inside_the_map(grid_coords, map_res, curr_intersection)
		&& !wall_check(grid_coords, map_res))
	{	
		determine_steps(&x_step, &y_step, player->ray_angle, ray_angle_in_rad);
		find_wall(curr_intersection, x_step, y_step, map_res);
	}
	return ;
}
