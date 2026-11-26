/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:04:56 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/26 15:33:54 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Headers to check:
// -/usr/include/X11/X.h for events and masks
// -/usr/include/X11/keysymdef.h for keycodes
// -mlx.h for hook declarations

int	movement(int keycode, void *params)
{
	t_params	*params_ptr;
	double		angle_of_mov;
	double		x_step;
	double		y_step;

	params_ptr = params;
	//
	printf("Viewing angle: %d\n", params_ptr->player->viewing_angle);
	//
	if (keycode == XK_Left)
	{
		if (params_ptr->player->viewing_angle != 359)
			params_ptr->player->viewing_angle += ROTATION_SPEED;
		else
			params_ptr->player->viewing_angle = 0 + ROTATION_SPEED - 1;
	}
	else if (keycode == XK_Right)
	{
		if (params_ptr->player->viewing_angle != 0)
			params_ptr->player->viewing_angle -= ROTATION_SPEED;
		else
			params_ptr->player->viewing_angle = 360 - ROTATION_SPEED;
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
		x_step = WALKING_SPEED * cos(angle_of_mov);
		y_step = WALKING_SPEED * sin(angle_of_mov);

		// Check new coords are not inside a wall
		// If both coords are inside a wall, no new frame is rendered
		// If only one coord is inside a wall, the one that is not is assigned
		// to the player's corresponding coord, and the one that is gets replaced
		// by the coord next to the wall, moving together with the other one

		params_ptr->player->coords[X] += x_step;
		params_ptr->player->coords[Y] -= y_step;
	}
	// LEFT OFF HERE: Bugs appear when going from 0 to 359 degrees
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
