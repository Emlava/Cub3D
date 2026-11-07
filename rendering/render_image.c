/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/07 17:57:09 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	correct_fishbowl_effect(double ray_length, double ray_angle,
	unsigned int viewing_angle)
{
	double	ray_and_view_diff;
	double	diff_in_radians;

	ray_and_view_diff = viewing_angle - ray_angle;
	if (ray_and_view_diff < 0)
	{
		// The viewing angle is to the left of degree 0, and the ray is to the right
		if (ray_angle > (viewing_angle + (FOV / 2)))
			ray_and_view_diff += 360;
		else // The ray is to the left of the viewing angle
		ray_and_view_diff = -ray_and_view_diff;
	}
	diff_in_radians = ray_and_view_diff * (PI / 180);
	ray_length *= cos(diff_in_radians);
	return ;
}

void	render_image(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	double	ray_angle;
	int		column;
	double	ray_length;

	ray_angle = player->viewing_angle + (FOV / 2);
	if (ray_angle < 0)
		ray_angle += 360;
	column = 0;
	mlx_res->img = mlx_new_image(mlx_res->mlx_id,
		mlx_res->screen_size[X], mlx_res->screen_size[Y]);
	if (!mlx_res->img)
		clean_and_exit(mlx_res, map_res, EXIT_FAILURE);
	while (column < mlx_res->screen_size[X])
	{
		ray_length = cast_ray(player->coords, map_res->map, ray_angle);
		correct_fishbowl_effect(ray_length, ray_angle, player->viewing_angle);
		
		// draw column in image

		ray_angle -= player->angle_between_rays;
		if (ray_angle < 0)
			ray_angle += 360;
		column += 1;
	}
	return ;
}
