/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/07 17:57:02 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	check_horizontal_intersections(int player_coords[2], char **map,
	double ray_angle, int curr_intersection[2])
{
	
}

static void	check_vertical_intersections(int player_coords[2], char **map,
	double ray_angle, int curr_intersection[2])
{}

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
