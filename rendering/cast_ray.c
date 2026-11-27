/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 18:25:59 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static double	d_from_player_to_wall(double player_coords[2],
	double wall_coords[2])
{
	double	x_diff;
	double	y_diff;

	x_diff = player_coords[X] - wall_coords[X];
	y_diff = player_coords[Y] - wall_coords[Y];
	return (sqrt(pow(x_diff, 2.0) + pow(y_diff, 2.0)));
}

int	cast_ray(t_player_res *player, t_map_res *map_res)
{
	double			ray_angle_in_rad;
	double			distance_h;
	double			distance_v;

	ray_angle_in_rad = degrees_to_rad(player->curr_r_angle);
	check_horizontal_intersections(player, map_res,
		ray_angle_in_rad);
	check_vertical_intersections(player, map_res,
		ray_angle_in_rad);
	distance_h = d_from_player_to_wall(player->coords,
		player->curr_h_wall_intersection);
	distance_v = d_from_player_to_wall(player->coords,
		player->curr_v_wall_intersection);
	if (distance_h < distance_v)
	{
		player->curr_r_length = distance_h;
		if (player->curr_r_angle < 180)
			return (NORTH);
		return (SOUTH);
	}
	player->curr_r_length = distance_v;
	if (player->curr_r_angle > 90 && player->curr_r_angle < 270)
		return (WEST);
	return (EAST);
}
