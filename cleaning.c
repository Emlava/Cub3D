/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:23:12 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/25 11:27:54 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map_res(t_map_res *map_res)
{
	int	i;

	i = 0;
	if (map_res->north)
		free(map_res->north);
	if (map_res->south)
		free(map_res->south);
	if (map_res->east)
		free(map_res->east);
	if (map_res->west)
		free(map_res->west);
	if (map_res->map)
	{
		while (map_res->map[i])
			free(map_res->map[i++]);
		free(map_res->map);
	}
	return ;
}