/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 14:03:24 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 18:19:11 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	find_nearest_intersection(t_player_res *player,
	double ray_angle_in_rad)
{
	player->curr_h_wall_intersection[Y]
	= (int)(player->coords[Y] / WORLD_SIDE_LENGTH) * WORLD_SIDE_LENGTH;
	if (player->curr_r_angle > 180) // Facing down
		player->curr_h_wall_intersection[Y] += WORLD_SIDE_LENGTH;
	player->curr_h_wall_intersection[X] = player->coords[X]
	+ (player->coords[Y] - player->curr_h_wall_intersection[Y])
	/ tan(ray_angle_in_rad);
	return ;
}

static void	define_grid_coords(t_player_res *player, int grid_coords[2])
{
	if (player->curr_h_wall_intersection[X] < 0
		|| player->curr_h_wall_intersection[Y] < 0)
	{
		grid_coords[X] = -1;
		grid_coords[Y] = -1;
		return ;
	}
	grid_coords[X] = player->curr_h_wall_intersection[X] / WORLD_SIDE_LENGTH;
	if (player->curr_r_angle < 180) // Facing up
		grid_coords[Y] = (player->curr_h_wall_intersection[Y] - 1)
		/ WORLD_SIDE_LENGTH;
	else
		grid_coords[Y] = player->curr_h_wall_intersection[Y] / WORLD_SIDE_LENGTH;
	return ;
}

// The signed is flipped for x_step if we're facing down, as the tangent
// of the angle divided by the side length will always be the opposite sign
// of the one we need (the tangent is negative only if cos and sin are of different signs)
static void	determine_steps(double *x_step, double *y_step, double curr_r_angle,
	double ray_angle_in_rad)
{
	*x_step = WORLD_SIDE_LENGTH / tan(ray_angle_in_rad);
	if (curr_r_angle > 180)
	{
		*x_step = -(*x_step);
		*y_step = WORLD_SIDE_LENGTH;
	}
	 else
		*y_step = -WORLD_SIDE_LENGTH;
	return ;
}

void	check_horizontal_intersections(t_player_res *player, t_map_res *map_res,
	double ray_angle_in_rad)
{
	int		grid_coords[2];
	double	x_step;
	double	y_step;

	// Manage a ray parallel to grid lines
	if (fabs(player->curr_r_angle) < 0.0001
	|| fabs(player->curr_r_angle - 360) < 0.0001
	|| fabs(player->curr_r_angle - 180) < 0.0001)
	{
		player->curr_h_wall_intersection[X] = INT_MAX;
		player->curr_h_wall_intersection[Y] = INT_MAX;
		return ;
	}
	find_nearest_intersection(player, ray_angle_in_rad);
	determine_steps(&x_step, &y_step, player->curr_r_angle, ray_angle_in_rad);
	define_grid_coords(player, grid_coords);
	while (is_inside_the_map(grid_coords, map_res,
		player->curr_h_wall_intersection)
		&& !wall_check(grid_coords, map_res->map))
	{
		player->curr_h_wall_intersection[X] += x_step;
		player->curr_h_wall_intersection[Y] += y_step;
		define_grid_coords(player, grid_coords);
	}
	return ;
}
