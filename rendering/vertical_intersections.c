/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 14:43:01 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 18:22:21 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	find_nearest_intersection(t_player_res *player,
	double ray_angle_in_rad)
{
	player->curr_v_wall_intersection[X]
		= (int)(player->coords[X] / WORLD_SIDE_LENGTH) * WORLD_SIDE_LENGTH;
	if (player->curr_r_angle < 90 || player->curr_r_angle > 270) // Facing right
		player->curr_v_wall_intersection[X] += WORLD_SIDE_LENGTH;
	player->curr_v_wall_intersection[Y] = player->coords[Y]
		+ (player->coords[X] - player->curr_v_wall_intersection[X])
		* tan(ray_angle_in_rad);
	return ;
}

static void	define_grid_coords(t_player_res *player, int grid_coords[2])
{
	if (player->curr_v_wall_intersection[X] < 0
		|| player->curr_v_wall_intersection[Y] < 0)
	{
		grid_coords[X] = -1;
		grid_coords[Y] = -1;
		return ;
	}
	if (player->curr_r_angle > 90 && player->curr_r_angle < 270) // Facing left
		grid_coords[X] = (player->curr_v_wall_intersection[X] - 1)
		/ WORLD_SIDE_LENGTH;
	else
		grid_coords[X] = player->curr_v_wall_intersection[X]
		/ WORLD_SIDE_LENGTH;
	grid_coords[Y] = player->curr_v_wall_intersection[Y] / WORLD_SIDE_LENGTH;
	return ;
}

// cf. determine_steps from horizontal_intersections.c
static void	determine_steps(double *x_step, double *y_step, double curr_r_angle,
	double ray_angle_in_rad)
{
	*y_step = WORLD_SIDE_LENGTH * tan(ray_angle_in_rad);
	if (curr_r_angle > 90 && curr_r_angle < 270) // Facing left
		*x_step = -WORLD_SIDE_LENGTH;
	else
	 {
		*x_step = WORLD_SIDE_LENGTH;
		*y_step = -(*y_step);
	 }
	return ;
}

void	check_vertical_intersections(t_player_res *player, t_map_res *map_res,
	double ray_angle_in_rad)
{
	int		grid_coords[2];
	double	x_step;
	double	y_step;
	
	// Manage a ray parallel to grid lines
	if (fabs(player->curr_r_angle - 90) < 0.0001
	|| fabs(player->curr_r_angle - 270) < 0.0001)
	{
		player->curr_v_wall_intersection[X] = INT_MAX;
		player->curr_v_wall_intersection[Y] = INT_MAX;
		return ;
	}
	find_nearest_intersection(player, ray_angle_in_rad);
	determine_steps(&x_step, &y_step, player->curr_r_angle, ray_angle_in_rad);
	define_grid_coords(player, grid_coords);
	while (is_inside_the_map(grid_coords, map_res, player->curr_v_wall_intersection)
		&& !wall_check(grid_coords, map_res->map))
	{
		player->curr_v_wall_intersection[X] += x_step;
		player->curr_v_wall_intersection[Y] += y_step;
		define_grid_coords(player, grid_coords);
	}
	return ;
}
