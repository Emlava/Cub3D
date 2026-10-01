/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:43:37 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/01 19:46:17 by elara-va         ###   ########.fr       */
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

static void	store_file_info(int fd, t_map_res *map_res) //
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

void	process_file(int ac, char *av[], t_map_res *map_res) //
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
