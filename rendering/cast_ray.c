/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:55:47 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/16 19:40:15 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static double	d_from_player_to_wall(int player_coords[2], int wall_coords[2])
{
	int	x_diff;
	int	y_diff;

	x_diff = player_coords[X] - wall_coords[X];
	y_diff = player_coords[Y] - wall_coords[Y];
	return (sqrt(pow((double)x_diff, 2.0) + pow((double)y_diff, 2.0)));
}

void	cast_ray(t_player_res *player, t_map_res *map_res)
{
	int				horizontal_wall_intersection[2];
	int				vertical_wall_intersection[2];
	unsigned int	distance_h;
	unsigned int	distance_v;

	check_horizontal_intersections(player, map_res, horizontal_wall_intersection);
	check_vertical_intersections(player, map_res, vertical_wall_intersection);
	distance_h = d_from_player_to_wall(player->coords, horizontal_wall_intersection);
	distance_v = d_from_player_to_wall(player->coords, vertical_wall_intersection);
	if (distance_h < distance_v)
		player->ray_length = distance_h;
	else
	player->ray_length = distance_v;
	return ;
}
