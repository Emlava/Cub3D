/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:43:37 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/29 21:26:36 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	store_field(char *line, t_map_res *map_res)
{
	ignore_leading_white_space(line);
	if (!(*line))
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (get_north_texture(line + 3, map_res));
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (get_south_texture(line + 3, map_res));
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (get_east_texture(line + 3, map_res));
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (get_west_texture(line + 3, map_res));
	else if (line[0] == 'C' && ft_isspace(line[1]))
		return (get_color(line + 2, map_res, 'C'));
	else if (line[0] == 'F' && ft_isspace(line[1]))
		return (get_color(line + 2, map_res, 'F'));
	else
		return (-1);
}

void	store_textures_and_colors(char **line, t_map_res *map_res,
	int *line_count, int fd)
{
	while (*line && line_is_not_map(*line))
	{
		if (store_field(*line, map_res) == -1) //
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

int	allocate_buff_node(t_map_buff *map_buff, t_map_res *map_res, char *line, int fd)
{
	map_buff = malloc(sizeof(t_map_buff));
	if (!map_buff)
	{
		free_map_res(map_res);
		free(line);
		close (fd);
		ft_dprintf(2, "malloc() failure\n");
		return (-1);
	}
	map_buff->next = NULL;
	return (0);
}

t_bool	line_is_not_empty(char *line)
{
	ignore_leading_white_space(&line);
	if (!line)
		return (FALSE);
	return (TRUE);
}

void	store_map(char *line, t_map_res *map_res, int first_line_of_map, int fd)
{
	t_map_buff	*map_buff;
	t_map_buff	*curr_node;

	if (allocate_buff_node(map_buff, map_res, line, fd) == -1)
		exit(EXIT_FAILURE);
	curr_node = map_buff;
	while (line && line_is_not_empty(line))
	{
		if (curr_node != map_buff)
		{
			if (allocate_buff_node(curr_node->next, map_res, line, fd) == -1)
			{
				free_map_buff(map_buff);
				exit(EXIT_FAILURE);
			}
			curr_node = curr_node->next;
		}
		curr_node->row = line;
		line = get_next_line(fd);
	}
	while (line) // If we enter this loop, the current line is empty
	{
		free(line);
		line = get_next_line(fd);
		if (line_is_not_empty(line))
		{
			free(line);
			free_map_buff(map_buff);
			free_map_res(map_res);
			close(fd);
			ft_dprintf(2, "Error\nSomething was found after the map\n");
			exit(EXIT_FAILURE);
		}
	}
	close(fd);

	// KEEP GOING HERE

	// Copy map_buff into map_res->map
	free_map_buff(map_buff);
	// Parse map using first_line_of_map to keep track of the lines in case an error message is needed
	return ;
}

void	store_file_info(int fd, t_map_res *map_res)
{
	char	*line;
	int		line_count;

	line = get_next_line(fd);
	line_count = 1;
	store_textures_and_colors(&line, map_res, &line_count, fd);
	if (!line)
	{
		free_map_res(map_res);
		close(fd);
		ft_dprintf(2, "Error\nMissing map\n");
		exit(EXIT_FAILURE);
	}
	store_map(line, map_res, line_count, fd);
	return ;
}

void	process_file(int ac, char *av[], t_map_res *map_res)
{
	int	fd;

	if (ac != 2 || !file_extension_check(av[1]))
	{
		printf("This program takes one argument: "
			"a scene description file with the .cub extension\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	store_file_info(fd, map_res);
	close(fd);
	return ;
}
