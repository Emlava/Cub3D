/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:58:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/16 20:52:23 by elara-va         ###   ########.fr       */
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

static void	draw_column(t_img *img, t_player_res *player, t_mlx_res *mlx_res,
	int column)
{
	int	projected_wall_height;
	int	y;
	int	i;
	
	projected_wall_height = (WORLD_SIDE_LENGTH / player->ray_length)
		* player->d_to_proj_plane;
	y = (mlx_res->screen_size[Y] / 2)
		- (projected_wall_height / 2);
	if (y < 0) // Projected wall is taller than screen
		y = 0;
	//
	// printf("\nProjected wall height: %d\n", projected_wall_height);
	// printf("Screen height: %d\n", mlx_res->screen_size[Y]);
	// printf("Half of projected wall height: %d\n", projected_wall_height / 2);
	// printf("Half of screen height: %d\n", mlx_res->screen_size[Y] / 2);
	// printf("First half minus second half: %d", (mlx_res->screen_size[Y] / 2) - (projected_wall_height / 2));
	//
	
	// LEFT OFF HERE: The SEGFAULT is coming from mlx_put_image_to_window()
	// Already guarded against the projected wall being taller than the screen

	
	i = 0;
	while (i < projected_wall_height && y <= mlx_res->screen_size[Y]) // Should the second condition use < or <=?
	{
		draw_pixel(img, column, y, 0x000000FF);
		y += 1;
		i += 1;
	}
	return ;
}

void	render_image(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res)
{
	int		column;
	t_img	*img;

	player->ray_angle = player->viewing_angle + (FOV / 2);
	if (player->ray_angle < 0)
		player->ray_angle += 360;
	column = 0;
	img = &mlx_res->img;
	img->id = mlx_new_image(mlx_res->mlx_id,
		mlx_res->screen_size[X], mlx_res->screen_size[Y]);
	if (!img->id)
		clean_and_exit(mlx_res, map_res, EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->id, &img->bits_per_pixel, &img->size_line,
		&img->endian);
	if (!img->addr) // Does addr get freed with mlx_destroy_image()?
		clean_and_exit(mlx_res, map_res, EXIT_FAILURE);
	while (column < mlx_res->screen_size[X])
	{
		cast_ray(player, map_res);
		correct_fishbowl_effect(player);
		
		draw_column(img, player, mlx_res, column);

		player->ray_angle -= player->angle_between_rays;
		if (player->ray_angle < 0)
			player->ray_angle += 360;
		column += 1;
	}
	mlx_put_image_to_window(mlx_res->mlx_id, mlx_res->win, img, 0, 0);
	return ;
}
