/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:33:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/02 18:21:04 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	set_player_coords(int x, int y, t_player_res *player)
{
	player->coords[X] = (WORLDS_SIDE_LENGTH * x) + (WORLDS_SIDE_LENGTH / 2);
	player->coords[Y] = (WORLDS_SIDE_LENGTH * y) + (WORLDS_SIDE_LENGTH /2);
	return ;
}

static void	set_viewing_angle(char value, t_player_res *player)
{
	if (value == 'N')
		player->viewing_angle = 90;
	else if (value == 'S')
		player->viewing_angle = 270;
	else if (value == 'W')
		player->viewing_angle = 180;
	else if (value == 'E')
		player->viewing_angle = 0;
	return ;
}

void	parse_map(t_map_res *map_res, t_player_res *player)
{
	int		curr_line;
	int		x;
	int		y;
	char	value;

	curr_line = map_res->first_line_of_map;
	y = 0;
	player->coords[X] = -1;
	while (map_res->map[y])
	{
		x = 0;
		while (map_res->map[y][x] != '\n')
		{
			value = map_res->map[y][x];
			if (value == '0')
			{
				
			}
			else if ((value == 'N' || value == 'S' || value == 'W' || value == 'E')
				&& player->coords[X] == -1)
			{
				set_player_coords(x, y, player);
				set_viewing_angle(value, player);
				map_res->map[y][x] = '0';
			}
			else if (value == ' ')
			{
				
			}
			else if (value != '1')
			{
				free_map_res(map_res);
				ft_dprintf(2, "Error\nInvalid map value in line %d, column %d\n",
					curr_line, x);
				exit (EXIT_FAILURE);
			}
			x++;
		}
		y++;
		curr_line++;
	}

	return ;
}
