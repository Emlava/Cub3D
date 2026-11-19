/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fields.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:22:49 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/19 11:36:02 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_meridian_texture(char *line, t_map_res *map_res, char *direction)
{
	ignore_white_space(&line);
	if (*line == '\n' || empty_spaces_in_path(line))
		return (-1);
	if (ft_strncmp(direction, "NO", 2) == 0)
	{
		map_res->north = ft_strdup(line);
		if (!map_res->north)
			return (MALLOC_FAILURE);
		map_res->north[ft_strlen(map_res->north) - 1] = '\0';
	}
	else if (ft_strncmp(direction, "SO", 2) == 0)
	{
		map_res->south = ft_strdup(line);
		if (!map_res->south)
			return (MALLOC_FAILURE);
		map_res->south[ft_strlen(map_res->south) - 1] = '\0';
	}
	return (0);
}

int	get_parallel_texture(char *line, t_map_res *map_res, char *direction)
{
	ignore_white_space(&line);
	if (*line == '\n' || empty_spaces_in_path(line))
		return (-1);
	if (ft_strncmp(direction, "WE", 2) == 0)
	{
		map_res->west = ft_strdup(line);
		if (!map_res->west)
			return (MALLOC_FAILURE);
		map_res->west[ft_strlen(map_res->west) - 1] = '\0';
	}
	else if (ft_strncmp(direction, "EA", 2) == 0)
	{
		map_res->east = ft_strdup(line);
		if (!map_res->east)
			return (MALLOC_FAILURE);
		map_res->east[ft_strlen(map_res->east) - 1] = '\0';
	}
	return (0);
}

static void	go_to_next_color(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
	if (**line == ',' && *(*line + 1) != '\n')
		(*line)++;
	ignore_white_space(line);
}

static int	rgb_to_single_int(int rgb[3])
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	while (i < 3)
	{
		color <<= 8;
		color |= rgb[i];
		i += 1;
	}
	return (color);
}

int	get_color(char *line, t_map_res *map_res, char c)
{
	int	i;
	int	rgb[3];

	i = 0;
	ignore_white_space(&line);
	while (*line != '\n')
	{
		if (i > 2 || !ft_isdigit(*line))
			return (-1);
		rgb[i] = ft_atoi(line);
		if (rgb[i] > 255)
			return (-1);
		i += 1;
		go_to_next_color(&line);
	}
	if (i < 3)
		return (-1);
	if (c == 'C')	
		map_res->ceiling = rgb_to_single_int(rgb);
	else
		map_res->floor = rgb_to_single_int(rgb);
	return (0);
}
