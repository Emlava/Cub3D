/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 18:38:07 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/12 19:30:26 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	manage_malloc_failure(t_map_res *map_res, t_map_buff *map_buff)
{
	free_map_buff(map_buff);
	free_map_res(map_res);
	ft_dprintf(2, "malloc() failure\n");
	exit(EXIT_FAILURE);
}

t_bool	orthogonal_space(char **map, int x, int y)
{
	char	left;
	char	right;
	char	above;
	char	below;

	left = map[y][x - 1];
	right = map[y][x + 1];
	above = map[y - 1][x];
	below = map[y + 1][x];
	if (left == ' ' || right == ' ' || above == ' ' || below == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	row_is_empty(char *line)
{
	while (*line == ' ')
		line++;
	if (*line)
		return (FALSE);
	return (TRUE);
}

void	check_player_is_present(int player_coord_x, t_map_res *map_res)
{
	if (player_coord_x != -1)
		return ;
	free_map_res(map_res);
	ft_dprintf(2, "Error\nNo player found\n");
	exit (EXIT_FAILURE);
}

void	remove_trailing_empty_rows(t_map_res *map_res, int y)
{
	while (row_is_empty(map_res->map[y]))
	{
		free(map_res->map[y]);
		map_res->map[y] = NULL;
		map_res->nbr_of_rows--;
		y--;
	}
	return ;
}
