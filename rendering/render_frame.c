/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/22 12:19:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	correct_fishbowl_effect(t_player_res *player)
{
	double	ray_and_view_diff;
	double	diff_in_radians;

	ray_and_view_diff = player->viewing_angle - player->ray_angle;
	if (ray_and_view_diff < 0)
	{
		// The viewing angle is to the left of degree 0, and the ray is to the right
		if (player->ray_angle > (player->viewing_angle + (FOV / 2)))
			ray_and_view_diff += 360;
		else // The ray is to the left of the viewing angle
		ray_and_view_diff = -ray_and_view_diff;
	}
	diff_in_radians = (ray_and_view_diff * PI) / 180;
	player->ray_length *= cos(diff_in_radians);
	return ;
}

static void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line) + (x * (img->bits_per_pixel / 8));
	*((unsigned int*)dst) = color;
	return ;
}

static void	draw_column(t_mlx_res *mlx_res, t_player_res *player, t_map_res *map_res,
	int column)
{
	int	projected_wall_height;
	int	wall_start_position;
	int	y;
	int	i;
	
	projected_wall_height = (int)round((WORLD_SIDE_LENGTH / player->ray_length)
		* player->d_to_proj_plane);
	//
	// static int	j;
	
	// if (!j)
	// {
	// 	printf("Projected wall height: %d\n", projected_wall_height);
	// 	j++;
	// }
	//

	wall_start_position = (mlx_res->screen_size[Y] / 2)
		- (projected_wall_height / 2);
	if (wall_start_position < 0) // Projected wall is taller than screen
		wall_start_position = 0;
	y = 0;

	// LEFT OFF HERE: Here we find the biggest step on the left
	// static int	consec_start_positions[2];

	// if (!column)
	// 	consec_start_positions[0] = wall_start_position;
	// else if (column == 1)
	// 	consec_start_positions[1] = wall_start_position;
	// else
	// {
	// 	consec_start_positions[0] = consec_start_positions[1];
	// 	consec_start_positions[1] = wall_start_position;
	// }
	// if (column && consec_start_positions[1] - consec_start_positions[0] > 15)
	// 	printf("Column of step: %d\n", column - 1);
	//

	// Draw ceiling slice
	while (y < wall_start_position)
	{
		//
			// if (column == 378)
			// if (column == 1407)
			// {
			// 	draw_pixel(&mlx_res->img, column, y, 0x0000FF00);
			// 	y += 1;
			// 	continue ;
			// }
		//
		draw_pixel(&mlx_res->img, column, y, map_res->ceiling);
		y += 1;
	}
	
	i = 0;
	// LEFT OFF HERE: Manage the texture of the current wall slice.
	// Figure out how to know on what side of the map is the wall.
	// Is it by checking the actual map coordinates or the ray angle?
	// Draw wall slice
	while (i < projected_wall_height && y < mlx_res->screen_size[Y])
	{
		draw_pixel(&mlx_res->img, column, y, 0x00663300);
		y += 1;
		i += 1;
	}
	// Draw floor slice
	while (y < mlx_res->screen_size[Y])
	{
		draw_pixel(&mlx_res->img, column, y, map_res->floor);
		y += 1;
	}
	return ;
}

void	render_frame(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	int		column;

	player->ray_angle = player->viewing_angle + (FOV / 2);
	if (player->ray_angle < 0)
		player->ray_angle += 360;
	column = 0;
	while (column < mlx_res->screen_size[X])
	{
		cast_ray(player, map_res, column);
		correct_fishbowl_effect(player);
		draw_column(mlx_res, player, map_res, column);
		player->ray_angle -= player->angle_between_rays;
		if (player->ray_angle < 0)
			player->ray_angle += 360;
		column += 1;
	}
	mlx_put_image_to_window(mlx_res->mlx_id, mlx_res->win, mlx_res->img.id, 0, 0);
	return ;
}
