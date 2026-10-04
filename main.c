/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:41:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/04 14:04:54 by elara-va         ###   ########.fr       */
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

int	main(int ac, char *av[])
{
	t_map_res		map_res;
	t_player_res	player;
	
	// t_mlx_res	mlx_res;

	init_map_res(&map_res);
	// Store the contents of the given file in the map struct while parsing
	process_file(ac, av, &map_res, &player);

	//
	int	i = 0;
	while (map_res.map[i] && map_res.map[i][0])
	{
		ft_printf("%s\n", map_res.map[i]);
		i++;
	}
	//

	// mlx_res.mlx_id = mlx_init();
	// if (!mlx_res.mlx_id)
	// 	exit(EXIT_FAILURE);
	// mlx_get_screen_size(mlx_res.mlx_id, &mlx_res.screen_size[X], &mlx_res.screen_size[Y]);
	
	// Create first image using the given map's starting position
	
	// mlx_res.win = mlx_new_window(mlx_res.mlx_id, mlx_res.screen_size[X], mlx_res.screen_size[Y], av[1]);
	// if (!mlx_res.win)
	// {
	// 	mlx_destroy_display(mlx_res.mlx_id);
	// 	exit(EXIT_FAILURE);
	// }
	
	// Put first image into the window
	// Set hooks so that the image is modified according to the events

	
	// mlx_loop(mlx_res.mlx_id);
	exit(EXIT_SUCCESS);
}
