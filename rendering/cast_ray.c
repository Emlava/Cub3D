/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/09 19:11:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// Probably add the width and length of the map as parameters (or the entire map_res struct)
static void	check_horizontal_intersections(int player_coords[2], char **map,
	double ray_angle, int curr_intersection[2])
{
	int		x_step;
	int		y_step;
	double	ray_angle_in_rad;

	if (ray_angle == 0 || ray_angle == 180)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	/* Find the nearest intersection coordinates */
	if (ray_angle < 180) // Facing up
	{
		curr_intersection[Y] = (int)(player_coords[Y] / WORLDS_SIDE_LENGTH)
			* WORLDS_SIDE_LENGTH - 1;
	}
	else // Facing down
	{
		curr_intersection[Y] = (int)(player_coords[Y] / WORLDS_SIDE_LENGTH)
			* WORLDS_SIDE_LENGTH + WORLDS_SIDE_LENGTH;
	}
	ray_angle_in_rad = ray_angle * (PI / 180);
	curr_intersection[X] = player_coords[X]
	+ round((player_coords[Y] - curr_intersection[Y]) / tan(ray_angle_in_rad));
	/******************************************/

	/* Check if there is a wall in the coordinates found, if not, determine x_ and y_step */
	/* and add them to the coordinates until we find a wall or are outside the map */
}

static void	check_vertical_intersections(int player_coords[2], char **map,
	double ray_angle, int curr_intersection[2])
{
	int		x_step;
	int		y_step;
	double	ray_angle_in_rad;
	
	if (ray_angle == 90 || ray_angle == 270)
	{
		curr_intersection[X] = INT_MAX;
		curr_intersection[Y] = INT_MAX;
		return ;
	}
	if (ray_angle < 90 || ray_angle > 270) // Facing right
	{}
	else // Facing left
	{}
	ray_angle_in_rad = ray_angle * (PI / 180);
}

static double	d_from_player_to_wall(int player_coords[2], int wall_coords[2])
{
	int	x_diff;
	int	y_diff;

	x_diff = player_coords[X] - wall_coords[X];
	y_diff = player_coords[Y] - wall_coords[Y];
	return (sqrt(pow((double)x_diff, 2.0) + pow((double)y_diff, 2.0)));
}

double	cast_ray(int player_coords[2], char **map, double ray_angle)
{
	int				horizontal_wall_intersection[2];
	int				vertical_wall_intersection[2];
	unsigned int	distance_h;
	unsigned int	distance_v;

	check_horizontal_intersections(player_coords, map, ray_angle,
		horizontal_wall_intersection);
	check_vertical_intersections(player_coords, map, ray_angle,
		vertical_wall_intersection);
	distance_h = d_from_player_to_wall(player_coords, horizontal_wall_intersection);
	distance_v = d_from_player_to_wall(player_coords, vertical_wall_intersection);
	if (distance_h < distance_v)
		return (distance_h);
	return (distance_v);
}
