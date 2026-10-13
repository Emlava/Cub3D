/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 10:33:15 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/13 19:24:30 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// If the 0 is at the first or last columns
// If the 0 is at the last row (first is already covered when
// looking for the map after the fields)
// If the 0 is orthogonally surrounded by a space
static void	check_enclosure(t_map_res *map_res, int x, int y,
	int curr_file_line)
{
	int	last_grid_of_row;
	int	last_row;

	last_grid_of_row = ft_strlen(map_res->map[y]) - 1;
	last_row = map_res->nbr_of_rows - 1;
	if (x == 0 || x == last_grid_of_row || y == last_row
		|| orthogonal_space(map_res->map, x, y))
	{
		free_map_res(map_res);
		ft_dprintf(2, "Error\nA walkable square (0) in line %d, column %d, "
			"was placed next to an open space\n", curr_file_line, x + 1);
		exit(EXIT_FAILURE);
	}
	return ;
}

static void	set_players_position(int x, int y, t_player_res *player,
	char direction)
{
	player->coords[X] = (WORLDS_SIDE_LENGTH * x) + (WORLDS_SIDE_LENGTH / 2);
	player->coords[Y] = (WORLDS_SIDE_LENGTH * y) + (WORLDS_SIDE_LENGTH / 2);
	if (direction == 'N')
		player->viewing_angle = 90;
	else if (direction == 'S')
		player->viewing_angle = 270;
	else if (direction == 'W')
		player->viewing_angle = 180;
	else if (direction == 'E')
		player->viewing_angle = 0;
	return ;
}

static void	parse_row(t_map_res *map_res, int row, int curr_file_line,
	t_player_res *player)
{
	int		i;
	char	value;

	i = 0;
	while (map_res->map[row][i])
	{
		value = map_res->map[row][i];
		if (value == '0')
			check_enclosure(map_res, i, row, curr_file_line);
		else if ((value == 'N' || value == 'S' || value == 'W'
				|| value == 'E') && player->coords[X] == -1)
		{
			set_players_position(i, row, player, value);
			map_res->map[row][i] = '0';
			continue ;
		}
		else if (value != '1' && value != ' ')
		{
			free_map_res(map_res);
			ft_dprintf(2, "Error\nInvalid map value in line %d,"
				"column %d\n", curr_file_line, i + 1);
			exit (EXIT_FAILURE);
		}
		i++;
	}
}

void	parse_map(t_map_res *map_res, t_player_res *player)
{
	int		curr_file_line;
	int		curr_row;

	curr_file_line = map_res->first_line_of_map;
	curr_row = 0;
	player->coords[X] = -1;
	while (map_res->map[curr_row])
	{
		parse_row(map_res, curr_row, curr_file_line, player);
		curr_row++;
		curr_file_line++;
	}
	check_player_is_present(player->coords[X], map_res);
	remove_trailing_empty_rows(map_res, --curr_row);
	return ;
}
