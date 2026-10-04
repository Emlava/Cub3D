/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures_and_colors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 19:36:52 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/04 13:54:17 by elara-va         ###   ########.fr       */
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
	ignore_leading_white_space(&line);
	if (*line == '\n')
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (get_north_texture(line + 3, map_res));
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (get_south_texture(line + 3, map_res));
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (get_east_texture(line + 3, map_res));
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (get_west_texture(line + 3, map_res));
	else if (line[0] == 'C' && ft_isspace(line[1])
		&& map_res->ceiling_is_set == FALSE)
		return (get_color(line + 2, map_res, 'C'));
	else if (line[0] == 'F' && ft_isspace(line[1])
		&& map_res->floor_is_set == FALSE)
		return (get_color(line + 2, map_res, 'F'));
	else
		return (-1);
}

static t_bool	missing_field(t_map_res *map_res)
{
	if (!map_res->north || !map_res->south || !map_res->east || !map_res->west
		|| map_res->ceiling_is_set == FALSE || map_res->floor_is_set == FALSE)
		return (TRUE);
	return (FALSE);
}

void	store_textures_and_colors(char **line, t_map_res *map_res,
	int *line_count, int fd)
{
	while (*line && line_is_not_map(*line))
	{
		if (store_field(*line, map_res) == -1)
		{
			ft_dprintf(2, "Error\nLine %d of the given file is invalid\n",
				*line_count);
			free(*line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(*line);
		*line = get_next_line(fd);
		(*line_count)++;
	}
	if (missing_field(map_res))
	{
		ft_dprintf(2, "Error\nMissing texture or color\n");
		free(*line);
		close(fd);
		free_map_res(map_res);
		exit(EXIT_FAILURE);
	}
	return ;
}
