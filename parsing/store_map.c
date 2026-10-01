/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 19:40:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/01 19:58:50 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	allocate_buff_node(t_map_buff **node, t_map_res *map_res, char *line, int fd)
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

static void	store_and_update_line(t_map_buff *node, t_map_res *map_res, char **line, int fd)
{
	node->row = *line;
	map_res->nbr_of_rows++;
	*line = get_next_line(fd);
	return ;
}

static void	check_file_after_map(char *line, int fd, t_map_buff *map_buff, t_map_res *map_res)
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

static void	copy_map_from_buff(t_map_res *map_res, t_map_buff *map_buff)
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
	
	// Parse map (using first_line_of_map to keep track of the lines in case an error message is needed)
	//
	first_line_of_map++; // Just for the compiler not to complain now that we are not using this argument
	first_line_of_map--; // Just for the compiler not to complain now that we are not using this argument
	//
	return ;
}

