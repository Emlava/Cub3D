/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/22 12:04:49 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static double	d_from_player_to_wall(int player_coords[2], double wall_coords[2])
{
	double	x_diff;
	double	y_diff;

	x_diff = player_coords[X] - wall_coords[X];
	y_diff = player_coords[Y] - wall_coords[Y];
	return (sqrt(pow(x_diff, 2.0) + pow(y_diff, 2.0)));
}

void	cast_ray(t_player_res *player, t_map_res *map_res, int col) // Remove col
{
	double			horizontal_wall_intersection[2];
	double			vertical_wall_intersection[2];
	double			distance_h;
	double			distance_v;

	check_horizontal_intersections(player, map_res, horizontal_wall_intersection);
	check_vertical_intersections(player, map_res, vertical_wall_intersection);
	distance_h = d_from_player_to_wall(player->coords, horizontal_wall_intersection);
	distance_v = d_from_player_to_wall(player->coords, vertical_wall_intersection);
	if (distance_h < distance_v)
	{
		player->ray_length = distance_h;
		//
		if (col == 1407 || col == 1406 || col == 1408)
			printf("\nColumn: %d, Ray angle: %f, H hit: %f, %f, V hit: %f, %f, "
				"Winner: H, Ray length before correction: %f\n",
				col, player->ray_angle, horizontal_wall_intersection[X], horizontal_wall_intersection[Y],
			vertical_wall_intersection[X], vertical_wall_intersection[Y], player->ray_length);
		//
	}
	else
	{
		player->ray_length = distance_v;
		//
		if (col == 1407 || col == 1406 || col == 1408)
			printf("\nColumn: %d, Ray angle: %f, H hit: %f, %f, V hit: %f, %f, "
				"Winner: V, Ray length before correction: %f\n",
				col, player->ray_angle, horizontal_wall_intersection[X], horizontal_wall_intersection[Y],
			vertical_wall_intersection[X], vertical_wall_intersection[Y], player->ray_length);
		//
	}
	return ;
}
