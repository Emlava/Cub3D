/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 13:06:12 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	correct_fishbowl_effect(t_player_res *player)
{
	double	ray_and_view_diff;
	double	diff_in_radians;

	ray_and_view_diff = player->viewing_angle - player->ray_angle;
	diff_in_radians = degrees_to_rad(ray_and_view_diff);
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

// LEFT OFF HERE: I will need map_res to copy the textels from the textures to
// the wall slice
static void	draw_wall_slice(int projected_wall_height, int *y, t_mlx_res *mlx_res,
	t_column *column)
{
	int	i;
	int	texture_column;
	int	color;

	i = 0;
	while (i < projected_wall_height && *y < mlx_res->window_size[Y])
	{
		if (column->e_wall_type == NORTH)
		{
			texture_column = column->n % WORLD_SIDE_LENGTH;
			color = ;
		}
		else if (column->e_wall_type == SOUTH)
		{
			texture_column = column->n % WORLD_SIDE_LENGTH;
		}
		else if (column->e_wall_type == WEST)
		{
			texture_column = *y % WORLD_SIDE_LENGTH;
		}
		else
		{
			texture_column = *y % WORLD_SIDE_LENGTH;
		}
		
		draw_pixel(&mlx_res->img, column->n, *y, 0x00663300);
		*y += 1;
		i += 1;
	}
}

static void	draw_column(t_mlx_res *mlx_res, t_player_res *player, t_map_res *map_res,
	t_column *column)
{
	int	projected_wall_height;
	int	wall_start_position;
	int	y;
	
	projected_wall_height = round((WORLD_SIDE_LENGTH / player->ray_length)
		* player->d_to_proj_plane);

	wall_start_position = (mlx_res->window_size[Y] / 2)
		- (projected_wall_height / 2);
	if (wall_start_position < 0) // Projected wall is taller than screen
		wall_start_position = 0;
	y = 0;

	// Draw ceiling slice
	while (y < wall_start_position)
	{
		draw_pixel(&mlx_res->img, column->n, y, map_res->ceiling);
		y += 1;
	}
	
	draw_wall_slice(projected_wall_height, &y, mlx_res, column);

	// Draw floor slice
	while (y < mlx_res->window_size[Y])
	{
		draw_pixel(&mlx_res->img, column->n, y, map_res->floor);
		y += 1;
	}
	return ;
}

void	render_frame(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	t_column	column;

	player->ray_angle = player->viewing_angle + (FOV / 2);
	if (player->ray_angle > 359)
		player->ray_angle -= 360;
	column.n = 0;
	while (column.n < mlx_res->window_size[X])
	{
		column.e_wall_type = cast_ray(player, map_res);
		correct_fishbowl_effect(player);
		draw_column(mlx_res, player, map_res, &column);
		player->ray_angle -= player->angle_between_rays;
		if (player->ray_angle < 0)
			player->ray_angle += 360;
		column.n += 1;
	}
	mlx_put_image_to_window(mlx_res->mlx_id, mlx_res->win, mlx_res->img.id, 0, 0);
	return ;
}
