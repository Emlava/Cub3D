/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:33:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/02 12:14:05 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	parse_map(t_map_res *map_res, t_player_res *player)
{
	int	curr_line;
	int	x;
	int	y;

	curr_line = map_res->first_line_of_map;
	y = 0;
	player->coords[X] = -1;
	player->coords[Y] = -1;
	while (map_res->map[y])
	{
		x = 0;
		while (map_res->map[y][x] != '\n')
		{
			
		}
	}

	return ;
}
