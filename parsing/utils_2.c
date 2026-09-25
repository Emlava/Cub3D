/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:22:49 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/25 18:33:34 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_north_texture(char *line, t_map_res *map_res)
{
	ignore_leading_white_space(&line);
	if (!(*line) || map_res->north != NULL)
		return (-1);
	map_res->north = ft_strdup(line); // If malloc() fails here, the program will exit when checking for missing fields
	return (0);
}

int	get_south_texture(char *line, t_map_res *map_res)
{
	ignore_leading_white_space(&line);
	if (!(*line) || map_res->south != NULL)
		return (-1);
	map_res->south = ft_strdup(line); // If malloc() fails here, the program will exit when checking for missing fields
	return (0);
}

int	get_east_texture(char *line, t_map_res *map_res)
{
	ignore_leading_white_space(&line);
	if (!(*line) || map_res->east != NULL)
		return (-1);
	map_res->east = ft_strdup(line); // If malloc() fails here, the program will exit when checking for missing fields
	return (0);
}

int	get_west_texture(char *line, t_map_res *map_res)
{
	ignore_leading_white_space(&line);
	if (!(*line) || map_res->west != NULL)
		return (-1);
	map_res->west = ft_strdup(line); // If malloc() fails here, the program will exit when checking for missing fields
	return (0);
}

int	get_color(char *line, t_map_res *map_res, char c)
{
	int	i;

	i = 0;
	ignore_leading_white_space(&line);
	while (*line)
	{
		if (i > 2 || !ft_isdigit(*line))
			return (-1);
		if (c == 'C')
			map_res->ceiling[i++] = ft_atoi(line);
		else if (c == 'F')
			map_res->floor[i++] = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		ignore_leading_white_space(&line);
	}
	return (0);
}
