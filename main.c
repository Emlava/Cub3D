/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:41:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/23 20:58:32 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// For testing, delete later
void	print_info(t_player_res *player, t_mlx_res *mlx_res)
{
	ft_printf("Player's x coordinate: %d\n", player->coords[X]);
	ft_printf("Player's y coordinate: %d\n", player->coords[Y]);
	ft_printf("Player's viewing angle: %d\n", player->viewing_angle);
	printf("Player's distance to projection plane: %.2f\n", player->d_to_proj_plane);
	printf("Angle between rays: %g\n", player->angle_between_rays);
	printf("Width of screen: %d\n", mlx_res->screen_size[X]);
	printf("Height of screen: %d\n", mlx_res->screen_size[Y]);
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
	double	opposite;
	double	theta_in_rad;
	double	tan_of_theta;
	
	opposite = width_of_plane / 2.0;
	theta_in_rad = ((FOV / 2.0) * PI) / 180;
	tan_of_theta = tan(theta_in_rad);
	player->d_to_proj_plane = opposite / tan_of_theta;
	player->angle_between_rays = (double)FOV / width_of_plane;
	return ;
}

void	assign_handlers_params(t_params *params, t_map_res *map_res,
	t_player_res *player, t_mlx_res *mlx_res)
{
	params->map_res = map_res;
	params->player = player;
	params->mlx_res = mlx_res;
	return ;
}

void	assign_handlers_ptrs(t_handlers *handlers)
{
	handlers->esc_exit = esc_exit;
	return ;
}

int	main(int ac, char *av[])
{
	t_map_res		map_res;
	t_player_res	player;
	t_mlx_res		mlx_res;
	t_params		params;
	t_handlers		handlers;

	process_file(ac, av, &map_res, &player);
	prepare_display(&mlx_res, &map_res);
	get_player_info(&player, mlx_res.screen_size[X]);
	assign_handlers_params(&params, &map_res, &player, &mlx_res);
	assign_handlers_ptrs(&handlers);
	mlx_res.win = mlx_new_window(mlx_res.mlx_id, mlx_res.screen_size[X],
		mlx_res.screen_size[Y], av[1]);
	if (!mlx_res.win)
		clean_and_exit(&mlx_res, &map_res, EXIT_FAILURE);
	render_frame(&player, &mlx_res, &map_res);

	// Set hooks so that the image is modified according to the events
	mlx_key_hook(mlx_res.win, handlers.esc_exit, &params);
	mlx_loop(mlx_res.mlx_id);
	clean_and_exit(&mlx_res, &map_res, EXIT_SUCCESS);
}
