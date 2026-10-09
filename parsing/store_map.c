/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 19:40:34 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/09 16:13:08 by elara-va         ###   ########.fr       */
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
		return (MALLOC_FAILURE);
	}
	(*node)->row = NULL;
	(*node)->next = NULL;
	return (0);
}

static void	store_and_update_line(t_map_buff *node, t_map_res *map_res, char **line, int fd)
{
	size_t	row_len;

	node->row = *line;
	map_res->nbr_of_rows++;
	row_len = ft_strlen(node->row);
	if (row_len > map_res->size_of_longest_row)
		map_res->size_of_longest_row = row_len;
	*line = get_next_line(fd);
	return ;
}

static void	manage_malloc_failure(t_map_res *map_res, t_map_buff *map_buff)
{
	free_map_buff(map_buff);
	free_map_res(map_res);
	ft_dprintf(2, "malloc() failure\n");
	exit(EXIT_FAILURE);
}

static void	copy_and_space_pad_row(t_map_buff *map_buff, t_map_res *map_res, int i)
{
	int	j;

	j = 0;
	while (map_buff->row[j] && map_buff->row[j] != '\n')
	{
		map_res->map[i][j] = map_buff->row[j];
		j++;
	}
	while (j < (int)map_res->size_of_longest_row - 1)
	{
		map_res->map[i][j] = ' ';
		j++;
	}
	map_res->map[i][j] = '\0';
}

static void	copy_map_from_buff(t_map_res *map_res, t_map_buff *map_buff)
{
	int	i;

	map_res->map = malloc(sizeof(char*) * (map_res->nbr_of_rows + 1));
	if (!map_res->map)
		manage_malloc_failure(map_res, map_buff);
	i = 0;
	while (i < map_res->nbr_of_rows)
	{
		// + 1 is not needed when allocating because we replace '\n' with '\0'
		map_res->map[i] = malloc(sizeof(char) * (map_res->size_of_longest_row));
		if (!map_res->map[i])
			manage_malloc_failure(map_res, map_buff);
		copy_and_space_pad_row(map_buff, map_res, i);
		i++;
		map_buff = map_buff->next;	
	}
	map_res->map[i] = NULL;
	return ;
}

void	store_map(char *line, t_map_res *map_res, int fd)
{
	t_map_buff	*map_buff;
	t_map_buff	*curr_node;

	if (allocate_buff_node(&map_buff, map_res, line, fd) == MALLOC_FAILURE)
		exit(EXIT_FAILURE);
	store_and_update_line(map_buff, map_res, &line, fd);
	curr_node = map_buff;
	while (line)
	{
		if (allocate_buff_node(&curr_node->next, map_res, line, fd) == MALLOC_FAILURE)
		{
			free_map_buff(map_buff);
			exit(EXIT_FAILURE);
		}
		curr_node = curr_node->next;
		store_and_update_line(curr_node, map_res, &line, fd);
	}
	close(fd);
	copy_map_from_buff(map_res, map_buff);
	free_map_buff(map_buff);
	return ;
}

