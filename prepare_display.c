/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:22:30 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/27 19:36:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_mlx_res(t_mlx_res *mlx_res)
{
	mlx_res->mlx_id = NULL;
	mlx_res->win = NULL;
	mlx_res->img.id = NULL;
	mlx_res->north.id = NULL;
	mlx_res->south.id = NULL;
	mlx_res->west.id = NULL;
	mlx_res->east.id = NULL;
	return ;
}

static void	get_texture_info(t_texture *north, t_texture *south, t_texture *west,
	t_texture *east)
{
	north->addr = mlx_get_data_addr(north->id, &north->bits_per_pixel,
		&north->size_line, &north->endian);
	south->addr = mlx_get_data_addr(south->id, &south->bits_per_pixel,
		&south->size_line, &south->endian);
	west->addr = mlx_get_data_addr(west->id, &west->bits_per_pixel,
		&west->size_line, &west->endian);
	east->addr = mlx_get_data_addr(east->id, &east->bits_per_pixel,
		&east->size_line, &east->endian);
	return ;
}

static int	open_textures(t_mlx_res *mlx_res, t_map_res *map_res)
{
	mlx_res->north.id = mlx_xpm_file_to_image(mlx_res->mlx_id,
		map_res->north, &mlx_res->north.size[X], &mlx_res->north.size[Y]);
	if (!mlx_res->north.id)
		return (-1);
	mlx_res->south.id = mlx_xpm_file_to_image(mlx_res->mlx_id,
		map_res->south, &mlx_res->south.size[X], &mlx_res->south.size[Y]);
	if (!mlx_res->south.id)
		return (-1);
	mlx_res->west.id = mlx_xpm_file_to_image(mlx_res->mlx_id,
		map_res->west, &mlx_res->west.size[X], &mlx_res->west.size[Y]);
	if (!mlx_res->west.id)
		return (-1);
	mlx_res->east.id = mlx_xpm_file_to_image(mlx_res->mlx_id,
		map_res->east, &mlx_res->east.size[X], &mlx_res->east.size[Y]);
	if (!mlx_res->east.id)
		return (-1);
	get_texture_info(&mlx_res->north, &mlx_res->south, &mlx_res->west,
		&mlx_res->east);
	return (0);
}

static int	create_image(t_mlx_res *mlx_res)
{
	t_img	*img;

	img = &mlx_res->img;
	img->id = mlx_new_image(mlx_res->mlx_id, mlx_res->window_size[X],
		mlx_res->window_size[Y]);
	if (!img->id)
		return (-1);
	img->addr = mlx_get_data_addr(img->id, &img->bits_per_pixel,
		&img->size_line, &img->endian);
	return (0);
}

int	prepare_display(t_mlx_res *mlx_res, t_map_res *map_res)
{
	init_mlx_res(mlx_res);
	mlx_res->mlx_id = mlx_init();
	if (!mlx_res->mlx_id)
		return (-1);
	mlx_get_screen_size(mlx_res->mlx_id, &mlx_res->window_size[X],
		&mlx_res->window_size[Y]);
	mlx_res->window_size[X] *= 0.75;
	mlx_res->window_size[Y] *= 0.75;
	if (open_textures(mlx_res, map_res) == -1 || create_image(mlx_res) == -1)
		return (-1);
	return (0);
}
