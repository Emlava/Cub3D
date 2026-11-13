/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/13 14:26:46 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static t_bool	is_inside_the_map(int grid_x, int grid_y, t_map_res *map_res,
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

static t_bool	wall_check(int grid_x, int grid_y, t_map_res *map_res)
{
	if (map_res->map[grid_y][grid_x] == '1')
		return (TRUE);
	return (FALSE);
}

// LEFT OFF HERE: Find a better structure for this function
// and apply it to the next
static void	check_horizontal_intersections(int player_coords[2],
	t_map_res *map_res, double ray_angle, int curr_intersection[2])
{
	double	ray_angle_in_rad;
	int		grid_x;
	int		grid_y;
	int		x_step;
	int		y_step;

	// Avoid a tan of 0, which would lead to a division by 0
	if (ray_angle == 0 || ray_angle == 180)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	
	// Find the nearest intersection coordinates
	curr_intersection[Y] = (int)(player_coords[Y] / WORLD_SIDE_LENGTH)
		* WORLD_SIDE_LENGTH;
	if (ray_angle < 180) // Facing up
			curr_intersection[Y] -= 1;
	else // Facing down
			curr_intersection[Y] += WORLD_SIDE_LENGTH;
	ray_angle_in_rad = ray_angle * (PI / 180);
	curr_intersection[X] = player_coords[X]
	+ round((player_coords[Y] - curr_intersection[Y]) / tan(ray_angle_in_rad));
	grid_x = curr_intersection[X] / WORLD_SIDE_LENGTH;
	grid_y = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	if (!is_inside_the_map(grid_x, grid_y, map_res, curr_intersection)
		|| wall_check(grid_x, grid_y, map_res))
		return ;

	// Determine x_ and y_step and add them to curr_intersection
	// while inside the map and no wall found
	x_step = WORLD_SIDE_LENGTH / tan(ray_angle_in_rad);
	if (ray_angle > 90 && ray_angle < 270) // Facing left
		x_step = -x_step;
	y_step = WORLD_SIDE_LENGTH;
	if (ray_angle < 180)
		y_step = -y_step;
	curr_intersection[X] += x_step;
	curr_intersection[Y] += y_step;
	grid_x = curr_intersection[X] / WORLD_SIDE_LENGTH;
	grid_y = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	while (is_inside_the_map(grid_x, grid_y, map_res, curr_intersection)
		&& !wall_check(grid_x, grid_y, map_res))
	{
		curr_intersection[X] += x_step;
		curr_intersection[Y] += y_step;
		grid_x = curr_intersection[X] / WORLD_SIDE_LENGTH;
		grid_y = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	}
	return ;
}

static void	check_vertical_intersections(int player_coords[2], t_map_res *map_res,
	double ray_angle, int curr_intersection[2])
{
	double	ray_angle_in_rad;
	int		grid_x;
	int		grid_y;
	int		x_step;
	int		y_step;
	
	// Avoid a tan of 0, which would lead to a division by 0
	if (ray_angle == 90 || ray_angle == 270)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}

	// Find the nearest intersection coordinates
	curr_intersection[X] = (int)(player_coords[X] / WORLD_SIDE_LENGTH)
		* WORLD_SIDE_LENGTH;
	if (ray_angle < 90 || ray_angle > 270) // Facing right
		curr_intersection[X] += WORLD_SIDE_LENGTH;
	else // Facing left
		curr_intersection[X] -= 1;
	ray_angle_in_rad = ray_angle * (PI / 180);
	curr_intersection[Y] = player_coords[Y]
		+ round((player_coords[X] - curr_intersection[X]) * tan(ray_angle_in_rad));
	grid_x = curr_intersection[X] / WORLD_SIDE_LENGTH;
	grid_y = curr_intersection[Y] / WORLD_SIDE_LENGTH;
	if (!is_inside_the_map(grid_x, grid_y, map_res, curr_intersection)
		|| wall_check(grid_x, grid_y, map_res))
		return ;
	
	// Determine x_ and y_step and add them to curr_intersection
	// while inside the map and no wall found
	x_step = WORLD_SIDE_LENGTH;
	if (ray_angle > 90 && ray_angle < 270) // Facing left
		x_step = -x_step;
	y_step = WORLD_SIDE_LENGTH * tan(ray_angle_in_rad);
	if (ray_angle < 180)
		y_step = -y_step;
}

static double	d_from_player_to_wall(int player_coords[2], int wall_coords[2])
{
	int	x_diff;
	int	y_diff;

	x_diff = player_coords[X] - wall_coords[X];
	y_diff = player_coords[Y] - wall_coords[Y];
	return (sqrt(pow((double)x_diff, 2.0) + pow((double)y_diff, 2.0)));
}

double	cast_ray(int player_coords[2], t_map_res *map_res, double ray_angle)
{
	int				horizontal_wall_intersection[2];
	int				vertical_wall_intersection[2];
	unsigned int	distance_h;
	unsigned int	distance_v;

	check_horizontal_intersections(player_coords, map_res, ray_angle,
		horizontal_wall_intersection);
	check_vertical_intersections(player_coords, map_res, ray_angle,
		vertical_wall_intersection);
	distance_h = d_from_player_to_wall(player_coords, horizontal_wall_intersection);
	distance_v = d_from_player_to_wall(player_coords, vertical_wall_intersection);
	if (distance_h < distance_v)
		return (distance_h);
	return (distance_v);
}
