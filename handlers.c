/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:04:56 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/26 20:27:11 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Headers to check:
// -/usr/include/X11/X.h for events and masks
// -/usr/include/X11/keysymdef.h for keycodes
// -mlx.h for hook declarations

static t_bool	player_outside_the_map(int grid_coords[2], t_map_res *map_res)
{
	if (grid_coords[Y] < 0 || grid_coords[Y] >= map_res->nbr_of_rows
		|| grid_coords[X] < 0
		|| grid_coords[X] >= (int)map_res->size_of_longest_row
		|| map_res->map[grid_coords[Y]][grid_coords[X]] == ' ')
		return (TRUE);
	return (FALSE);	
}

// Check new coords are not inside a wall
// If both coords are inside a wall, no new frame is rendered
// If only one coord is inside a wall, the one that is not is assigned
// to the player's corresponding coord, and the one that is gets replaced
// by the coord next to the wall, moving together with the other one
static int	determine_new_coords(t_player_res *player, t_map_res *map_res,
	double angle_of_mov)
{
	double	x_step;
	double	y_step;
	int		grid_coords[2];

	x_step = UNITS_PER_STEP * cos(angle_of_mov);
	y_step = UNITS_PER_STEP * sin(angle_of_mov);

	// grid_coords[X] = round((player->coords[X] + x_step) / WORLD_SIDE_LENGTH);
	// grid_coords[Y] = round(player->coords[Y] / WORLD_SIDE_LENGTH);
	// while ((int)x_step && (player_outside_the_map(grid_coords, map_res)
	// 	|| wall_check(grid_coords, map_res->map)))
	// {
	// 	if (x_step > 0)
	// 		x_step -= 1;
	// 	else
	// 		x_step += 1;
	// 	grid_coords[X] = round((player->coords[X] + x_step) / WORLD_SIDE_LENGTH);
	// }

	// grid_coords[X] = round(player->coords[X] / WORLD_SIDE_LENGTH);
	// grid_coords[Y] = round((player->coords[Y] - y_step) / WORLD_SIDE_LENGTH);
	// while ((int)y_step && (player_outside_the_map(grid_coords, map_res)
	// 	|| wall_check(grid_coords, map_res->map)))
	// {
	// 	if (y_step > 0)
	// 		y_step -= 1;
	// 	else
	// 		y_step += 1;
	// 	grid_coords[Y] = round((player->coords[Y] - y_step) / WORLD_SIDE_LENGTH);
	// }
	//
	grid_coords[X] = round((player->coords[X] + x_step) / WORLD_SIDE_LENGTH);
	grid_coords[Y] = round((player->coords[Y] - y_step) / WORLD_SIDE_LENGTH);
	//
	if (!player_outside_the_map(grid_coords, map_res) && !wall_check(grid_coords, map_res->map))
	{
		player->coords[X] += x_step;
		player->coords[Y] -= y_step;
	}
	else
	{
		printf("Wall hit\n");
		return (INVALID_MOVEMENT);
	}

	//
	printf("step_x: %f, step_y: %f, player_x: %f, player_y: %f, grid_x: %d, grid_y: %d\n", x_step, y_step,
		player->coords[X], player->coords[Y], (int)(player->coords[X] / WORLD_SIDE_LENGTH),
		(int)(player->coords[Y] / WORLD_SIDE_LENGTH));
	//

	return (0);
}

int	movement(int keycode, void *params)
{
	t_params	*params_ptr;
	double		angle_of_mov;

	params_ptr = params;
	if (keycode == XK_Left)
	{
		if (params_ptr->player->viewing_angle != 359)
			params_ptr->player->viewing_angle += ROTATION_SPEED;
		else
			params_ptr->player->viewing_angle = 0 + ROTATION_SPEED - 1;
		//
		printf("Viewing angle: %d\n", params_ptr->player->viewing_angle);
		//
	}
	else if (keycode == XK_Right)
	{
		if (params_ptr->player->viewing_angle != 0)
			params_ptr->player->viewing_angle -= ROTATION_SPEED;
		else
			params_ptr->player->viewing_angle = 360 - ROTATION_SPEED;
		//
		printf("Viewing angle: %d\n", params_ptr->player->viewing_angle);
		//
	}
	else
	{
		if (keycode == XK_a)
			angle_of_mov = degrees_to_rad(params_ptr->player->viewing_angle + 90);
		else if (keycode == XK_w)
			angle_of_mov = degrees_to_rad(params_ptr->player->viewing_angle);
		else if (keycode == XK_d)
			angle_of_mov = degrees_to_rad(params_ptr->player->viewing_angle - 90);
		else if (keycode == XK_s)
			angle_of_mov = degrees_to_rad(params_ptr->player->viewing_angle - 180);
		else
			return (0);
		
		if (determine_new_coords(params_ptr->player, params_ptr->map_res,
			angle_of_mov) == INVALID_MOVEMENT)
			return (0);
	}
	render_frame(params_ptr->player, params_ptr->mlx_res, params_ptr->map_res);
	return (0);
}

int	esc_exit(int keycode, void *params)
{
	t_params	*params_ptr;

	if (keycode != XK_Escape)
		return (0);
	params_ptr = (t_params *)params;
	clean_and_exit(params_ptr->mlx_res, params_ptr->map_res, EXIT_SUCCESS);
	return (0);
}

int	cross_exit(void *params)
{
	t_params	*params_ptr;

	params_ptr = (t_params *)params;
	clean_and_exit(params_ptr->mlx_res, params_ptr->map_res, EXIT_SUCCESS);
	return (0);
}
