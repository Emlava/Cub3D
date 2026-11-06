/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 14:47:50 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/06 15:34:23 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	destroy_mlx_res(t_mlx_res *mlx_res)
{
	if (!mlx_res->mlx_id)
		return ;
	if (mlx_res->img)
		mlx_destroy_image(mlx_res->mlx_id, mlx_res->img);
	if (mlx_res->win)
		mlx_destroy_window(mlx_res->mlx_id, mlx_res->win);
	mlx_destroy_display(mlx_res->mlx_id);
	free(mlx_res->mlx_id);
	return ;
}

void	clean_and_exit(t_mlx_res *mlx_res, t_map_res *map_res, int exit_status)
{
	destroy_mlx_res(mlx_res);
	free_map_res(map_res);
	exit(exit_status);
}