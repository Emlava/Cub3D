/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:41:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/02 20:59:07 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map_res(t_map_res *map_res)
{
	map_res->north = NULL;
	map_res->south = NULL;
	map_res->west = NULL;
	map_res->east = NULL;
	map_res->ceiling_is_set = FALSE;
	map_res->floor_is_set = FALSE;
	map_res->map = NULL;
	map_res->nbr_of_rows = 0;
	map_res->size_of_longest_row = 0;
	return ;
}

// The distance to the projection plane is the adjacent side of the right triangle
// resulting from cutting in half the triangle formed by the player and both ends
// of the projection plane, considering the angle on the player's side as theta.
// The formula to get the size of the adjacent side of a right triangle is
// opposite / tan(θ)
// Consider that the oppposite side is half of the projection plane's width,
// and theta is half of the FOV
// The angle between subsequent rays is equal to FOV / plane's width
void	get_player_info(t_player_res *player, int width_of_plane)
{
	int		opposite;
	double	theta_in_rad;
	double	tan_of_theta;
	
	opposite = width_of_plane / 2;
	theta_in_rad = (FOV / 2) * (PI / 180);
	tan_of_theta = tan(theta_in_rad);
	player->d_to_proj_plane = (unsigned int)(opposite / tan_of_theta);
	player->angle_between_rays = (double)FOV / width_of_plane;
}

int	main(int ac, char *av[])
{
	t_map_res		map_res;
	t_player_res	player;
	t_mlx_res		mlx_res;

	init_map_res(&map_res);
	// Store the contents of the given file in the map struct while parsing
	process_file(ac, av, &map_res, &player);

	mlx_res.mlx_id = mlx_init();
	if (!mlx_res.mlx_id)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(mlx_res.mlx_id, &mlx_res.screen_size[X], &mlx_res.screen_size[Y]);
	get_player_info(&player, mlx_res.screen_size[X]);
	
	// Create first image using the given map's starting position
	
	mlx_res.win = mlx_new_window(mlx_res.mlx_id, mlx_res.screen_size[X], mlx_res.screen_size[Y], av[1]);
	if (!mlx_res.win)
	{
		mlx_destroy_display(mlx_res.mlx_id);
		exit(EXIT_FAILURE);
	}
	
	// Put first image into the window
	// Set hooks so that the image is modified according to the events

	
	mlx_loop(mlx_res.mlx_id);
	exit(EXIT_SUCCESS);
}
