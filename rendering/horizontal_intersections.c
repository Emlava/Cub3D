/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 14:03:24 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/17 21:28:11 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	find_nearest_intersection(double curr_intersection[2],
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

// The signed is flipped for x_step if we're facing down, as the tangent
// of the angle divided by the side length will always be the opposite sign
// of the one we need (the tangent is negative if cos and sin are of different signs)
static void	determine_steps(double *x_step, double *y_step, double ray_angle,
	double ray_angle_in_rad)
{
	*x_step = WORLD_SIDE_LENGTH / tan(ray_angle_in_rad);
	*y_step = WORLD_SIDE_LENGTH;
	if (ray_angle < 180)
	 {
		*x_step = -(*x_step);
		*y_step = -(*y_step);
	 }
	return ;
}

void	check_horizontal_intersections(t_player_res *player, t_map_res *map_res,
	double curr_intersection[2])
{
	double	ray_angle_in_rad;
	int		grid_coords[2];
	double	x_step;
	double	y_step;

	// Manage a ray parallel to grid lines
	if (fabs(player->ray_angle) < 0.0001
	|| fabs(player->ray_angle - 360) < 0.0001
	|| fabs(player->ray_angle - 180) < 0.0001)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	ray_angle_in_rad = (player->ray_angle * PI) / 180;
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
