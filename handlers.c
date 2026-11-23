/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:04:56 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/23 21:00:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Headers to check:
// -/usr/include/X11/X.h for events and masks
// -/usr/include/X11/keysymdef.h for keycodes
// -mlx.h for hook declarations

int	esc_exit(int keycode, void *params)
{
	t_params	*params_ptr;

	if (keycode != 0xff1b)
		return (0);
	params_ptr = (t_params *)params;
	clean_and_exit(params_ptr->mlx_res, params_ptr->map_res, EXIT_SUCCESS);
	return (0); // To avoid compilation warnings
}
