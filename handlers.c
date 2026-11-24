/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:04:56 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/24 21:02:08 by elara-va         ###   ########.fr       */
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

	params_ptr = params;
	// Arrows
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

	// WASD


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
	return (0); // To avoid compilation warnings
}

int	cross_exit(void *params)
{
	t_params	*params_ptr;

	params_ptr = (t_params *)params;
	clean_and_exit(params_ptr->mlx_res, params_ptr->map_res, EXIT_SUCCESS);
	return (0); // To avoid compilation warnings
}
