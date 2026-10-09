/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:22:49 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/09 17:58:56 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static t_bool	empty_spaces_in_path(char *path)
{
	while (*path && !ft_isspace(*path))
		path++;
	ignore_white_space(&path);
	if (*path && *path != '\n')
		return (TRUE);
	return (FALSE);
}

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
	}
	else if (ft_strncmp(direction, "SO", 2) == 0)
	{
		map_res->south = ft_strdup(line);
		if (!map_res->south)
			return (MALLOC_FAILURE);
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
	}
	else if (ft_strncmp(direction, "EA", 2) == 0)
	{
		map_res->east = ft_strdup(line);
		if (!map_res->east)
			return (MALLOC_FAILURE);
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

int	get_color(char *line, t_map_res *map_res, char c)
{
	int	i;
	int	color;

	i = 0;
	ignore_white_space(&line);
	while (*line != '\n')
	{
		if (i > 2 || !ft_isdigit(*line))
			return (-1);
		color = ft_atoi(line);
		if (color > 255)
			return (-1);
		if (c == 'C')
			map_res->ceiling[i++] = color;
		else if (c == 'F')
			map_res->floor[i++] = color;
		go_to_next_color(&line);
	}
	if (i < 3)
		return (-1);
	if (c == 'C')
			map_res->ceiling_is_set = TRUE;
	else if (c == 'F')
			map_res->floor_is_set = TRUE;
	return (0);
}
