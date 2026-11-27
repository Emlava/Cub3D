/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 19:35:16 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	correct_fishbowl_effect(t_player_res *player)
{
	double	ray_and_view_diff;
	double	diff_in_radians;

	ray_and_view_diff = player->viewing_angle - player->curr_r_angle;
	diff_in_radians = degrees_to_rad(ray_and_view_diff);
	player->curr_r_length *= cos(diff_in_radians);
	return ;
}

// static void	determine_texture_of_wall(t_column *column, t_player_res *player,
// 	t_mlx_res *mlx_res)
// {
// 	if (column->e_wall_type == NORTH)
// 	{
// 		column->texture = &mlx_res->north;
// 		// Check rounding
// 		column->texture->offset[X]
// 			= (int)player->curr_h_wall_intersection[X]
// 			% WORLD_SIDE_LENGTH * (column->texture->bits_per_pixel / 8);
// 	}
// 	else if (column->e_wall_type == SOUTH)
// 	{
// 		column->texture = &mlx_res->south;
// 		column->texture->offset[X]
// 			= (int)player->curr_h_wall_intersection[X]
// 			% WORLD_SIDE_LENGTH * (column->texture->bits_per_pixel / 8);
// 	}
// 	else if (column->e_wall_type == WEST)
// 	{
// 		column->texture = &mlx_res->west;
// 		column->texture->offset[X]
// 			= (int)player->curr_v_wall_intersection[Y]
// 			% WORLD_SIDE_LENGTH * (column->texture->bits_per_pixel / 8);
// 	}
// 	else
// 	{
// 		column->texture = &mlx_res->east;
// 		column->texture->offset[X]
// 			= (int)player->curr_v_wall_intersection[Y]
// 			% WORLD_SIDE_LENGTH * (column->texture->bits_per_pixel / 8);
// 	}
// 	column->texture->offset[Y] = 0;
// 	return ;
// }

static void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line) + (x * (img->bits_per_pixel / 8));
	*((unsigned int*)dst) = color;
	return ;
}

static void	draw_wall_slice(int projected_wall_height, t_mlx_res *mlx_res,
	t_column *column)
{
	int			i;
	int			color;
	// t_texture	*texture;
	
	i = 0;
	// texture = column->texture;
	//
	color = 0x64483c;
	//
	while (i < projected_wall_height && column->y < mlx_res->window_size[Y])
	{
		// color = *((unsigned int*)(texture->addr + texture->offset[Y]
		// 	+ texture->offset[X]));
		draw_pixel(&mlx_res->img, column->nbr, column->y, color);
		column->y += 1;
		i += 1;
		// column->texture->offset[Y] += column->texture->size_line;
	}
	return ;
}

static void	draw_column(t_mlx_res *mlx_res, t_player_res *player, t_map_res *map_res,
	t_column *column)
{
	int	projected_wall_height;
	int	wall_start_position;
	
	projected_wall_height = round((WORLD_SIDE_LENGTH / player->curr_r_length)
		* player->d_to_proj_plane);

	wall_start_position = (mlx_res->window_size[Y] / 2)
		- (projected_wall_height / 2);
	if (wall_start_position < 0) // Projected wall is taller than screen
		wall_start_position = 0;
	column->y = 0;

	// Draw ceiling slice
	while (column->y < wall_start_position)
	{
		draw_pixel(&mlx_res->img, column->nbr, column->y, map_res->ceiling);
		column->y += 1;
	}
	
	// determine_texture_of_wall(column, player, mlx_res);
	draw_wall_slice(projected_wall_height, mlx_res, column);

	// Draw floor slice
	while (column->y < mlx_res->window_size[Y])
	{
		draw_pixel(&mlx_res->img, column->nbr, column->y, map_res->floor);
		column->y += 1;
	}
	return ;
}

void	render_frame(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	t_column	column;

	player->curr_r_angle = player->viewing_angle + (FOV / 2);
	if (player->curr_r_angle > 359)
		player->curr_r_angle -= 360;
	column.nbr = 0;
	while (column.nbr < mlx_res->window_size[X])
	{
		column.e_wall_type = cast_ray(player, map_res);
		correct_fishbowl_effect(player);
		draw_column(mlx_res, player, map_res, &column);
		player->curr_r_angle -= player->angle_between_rays;
		if (player->curr_r_angle < 0)
			player->curr_r_angle += 360;
		column.nbr += 1;
	}
	mlx_put_image_to_window(mlx_res->mlx_id, mlx_res->win, mlx_res->img.id, 0, 0);
	return ;
}
