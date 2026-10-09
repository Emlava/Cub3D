/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:43:37 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/09 09:21:41 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
	Things the program should be able to catch so far:
	-Missing fields
	-Invalid fields
	-Repeated fields
	-Missing map
	-Invalid characters in map
	-Missing player in map
*/


static void	store_file_info(int fd, t_map_res *map_res, t_player_res *player)
{
	char	*line;
	int		line_count;

	line = get_next_line(fd);
	line_count = 1;
	store_textures_and_colors(&line, map_res, &line_count, fd);
	if (!line)
	{
		free_map_res(map_res);
		ft_dprintf(2, "Error\nMissing map\n");
		exit(EXIT_FAILURE);
	}
	// Check for invalid colors and permissions for textures
	map_res->first_line_of_map = line_count;
	store_map(line, map_res, fd);
	parse_map(map_res, player);
	return ;
}

void	process_file(int ac, char *av[], t_map_res *map_res, t_player_res *player)
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
	store_file_info(fd, map_res, player);
	return ;
}
