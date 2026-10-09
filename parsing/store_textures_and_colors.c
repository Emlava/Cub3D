/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures_and_colors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 19:36:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/09 17:23:48 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static t_bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (TRUE);
	return (FALSE);
}

static t_bool	line_is_not_map(char *line)
{
	if (is_map_char(*line))
	{
		line++;
		while (is_map_char(*line))
			line++;
		if (!*line || *line == '\n')
			return (FALSE);
	}
	return (TRUE);
}

static int	store_field(char *line, t_map_res *map_res)
{
	ignore_white_space(&line);
	if (*line == '\n')
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2])
		&& map_res->north == NULL)
		return (get_meridian_texture(line + 3, map_res, "NO"));
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2])
		&& map_res->south == NULL)
		return (get_meridian_texture(line + 3, map_res, "SO"));
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2])
		&& map_res->west == NULL)
		return (get_parallel_texture(line + 3, map_res, "WE"));
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2])
		&& map_res->east == NULL)
		return (get_parallel_texture(line + 3, map_res, "EA"));
	else if (line[0] == 'C' && ft_isspace(line[1])
		&& map_res->ceiling_is_set == FALSE)
		return (get_color(line + 2, map_res, 'C'));
	else if (line[0] == 'F' && ft_isspace(line[1])
		&& map_res->floor_is_set == FALSE)
		return (get_color(line + 2, map_res, 'F'));
	else
		return (-1);
}

static void	check_for_missing_fields(t_map_res *map_res, char *line)
{
	if (!map_res->north || !map_res->south || !map_res->east || !map_res->west
		|| map_res->ceiling_is_set == FALSE || map_res->floor_is_set == FALSE)
	{
		ft_dprintf(2, "Error\nMissing texture or color\n");
		free(line);
		free_map_res(map_res);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	store_textures_and_colors(char **line, t_map_res *map_res,
	int *line_count, int fd)
{
	int	ret_value;

	while (*line && line_is_not_map(*line))
	{
		ret_value = store_field(*line, map_res);
		{
			if (ret_value < 0)
			{
				if (ret_value == MALLOC_FAILURE)
					ft_dprintf(2, "malloc() failure\n");
				else
					ft_dprintf(2, "Error\nLine %d of the given file is invalid\n",
						*line_count);
				free(*line);
				free_map_res(map_res);
				exit(EXIT_FAILURE);
			}
		}
		free(*line);
		*line = get_next_line(fd);
		(*line_count)++;
	}
	check_for_missing_fields(map_res, *line);
	return ;
}
