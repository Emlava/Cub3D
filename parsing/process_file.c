/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:43:37 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/01 18:06:53 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Things the program should be able to catch so far:
	-Missing fields
	-Invalid fields
	-Repeated fields
	-Missing map
	-Content after map
*/

#include "../cub3D.h"

t_bool	line_is_not_map(char *line)
{
	if (*line == '1' || *line == ' ')
	{
		while (*line == '1' || *line == ' ')
			line++;
		if (!*line || *line == '\n')
			return (FALSE);
	}
	return (TRUE);
}

int	store_field(char *line, t_map_res *map_res)
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

int	allocate_buff_node(t_map_buff **node, t_map_res *map_res, char *line, int fd)
{
	*node = malloc(sizeof(t_map_buff));
	if (!*node)
	{
		free_map_res(map_res);
		free(line);
		close (fd);
		ft_dprintf(2, "malloc() failure\n");
		return (-1);
	}
	(*node)->next = NULL;
	return (0);
}

t_bool	line_is_not_empty(char *line)
{
	if (!line)
		return (FALSE);
	ignore_leading_white_space(&line);
	if (*line == '\n')
		return (FALSE);
	return (TRUE);
}

void	check_file_after_map(char *line, int fd, t_map_buff *map_buff, t_map_res *map_res)
{
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
	return ;
}

void	copy_map_from_buff(t_map_res *map_res, t_map_buff *map_buff)
{
	int	i;

	map_res->map = malloc(sizeof(char*) * (map_res->nbr_of_rows + 1));
	if (!map_res->map)
	{
		free_map_buff(map_buff);
		free_map_res(map_res);
		ft_dprintf(2, "malloc() failure\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < map_res->nbr_of_rows)
	{
		map_res->map[i] = map_buff->row;
		i++;
		map_buff = map_buff->next;	
	}
	map_res->map[i] = NULL;
	return ;
}

void	store_and_update_line(t_map_buff *node, t_map_res *map_res, char **line, int fd)
{
	node->row = *line;
	map_res->nbr_of_rows++;
	*line = get_next_line(fd);
	return ;
}

void	store_map(char *line, t_map_res *map_res, int first_line_of_map, int fd)
{
	t_map_buff	*map_buff;
	t_map_buff	*curr_node;

	if (allocate_buff_node(&map_buff, map_res, line, fd) == -1)
		exit(EXIT_FAILURE);
	store_and_update_line(map_buff, map_res, &line, fd);
	curr_node = map_buff;
	while (line && line_is_not_empty(line))
	{
		if (allocate_buff_node(&curr_node->next, map_res, line, fd) == -1)
		{
			free_map_buff(map_buff);
			exit(EXIT_FAILURE);
		}
		curr_node = curr_node->next;
		store_and_update_line(curr_node, map_res, &line, fd);
	}
	check_file_after_map(line, fd, map_buff, map_res);
	close(fd);
	copy_map_from_buff(map_res, map_buff);
	free_map_buff(map_buff);
	//
	int	i = 0;
	
	while (map_res->map[i])
		ft_printf("%s", map_res->map[i++]);
	//
	// Parse map (using first_line_of_map to keep track of the lines in case an error message is needed)
	//
	first_line_of_map++; // Just for the compiler not to complain now that we are not using this argument
	first_line_of_map--; // Just for the compiler not to complain now that we are not using this argument
	//
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
	// Check for invalid colors and permissions for textures
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
	return ;
}
