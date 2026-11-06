/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/06 15:20:08 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	render_image(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	double	ray_angle;
	int		column;
	double	ray_length;

	ray_angle = player->viewing_angle - (FOV / 2);
	if (ray_angle < 0)
		ray_angle += 360;
	column = 0;
	mlx_res->img = mlx_new_image(mlx_res->mlx_id,
		mlx_res->screen_size[X], mlx_res->screen_size[Y]);
	if (!mlx_res->img)
		clean_and_exit(mlx_res, map_res, EXIT_FAILURE);
	while (column < mlx_res->screen_size[X])
	{
		// cast ray
		// draw column in image
		column += 1;
	}
	return ;
}
