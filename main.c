/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:41:02 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/24 19:50:05 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	file_extension_check(char *file)
{
	size_t	file_name_len;
	char	*extension;

	file_name_len = ft_strlen(file);
	if (file_name_len < 5)
		return (0);
	extension = ft_strnstr(file, ".cub", file_name_len);
	if (!extension || *(extension + 4) != '\0')
		return (0);
	return (1);
}

void	store_file_info(int fd, t_map_res *map_res)
{
	char	*line;
	int		line_count;

	line = get_next_line(fd);
	line_count = 1;
	while (line && line_is_not_map(line))
	{
		if (store_texture_or_color(line, map_res) == -1)
		{
			ft_dprintf(2, "Error\nLine %d of the given file is invalid\n", line_count);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (store_map_row(line, map_res) == -1)
		{
			ft_dprintf(2, "Error\nLine %d of the given file is invalid\n", line_count);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
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

int	main(int ac, char *av[])
{
	t_map_res	map_res;
	t_mlx_res	mlx_res;

	// Store the contents of the given file in the map struct while parsing
	process_file(ac, av, &map_res);

	mlx_res.mlx_id = mlx_init();
	if (!mlx_res.mlx_id)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(mlx_res.mlx_id, &mlx_res.size_x, &mlx_res.size_y);
	
	// Create first image using the given map's starting position
	
	mlx_res.win = mlx_new_window(mlx_res.mlx_id, mlx_res.size_x, mlx_res.size_x, av[1]);
	if (!mlx_res.win)
	{
		mlx_destroy_display(mlx_res.mlx_id);
		exit(EXIT_FAILURE);
	}
	
	// Put first image into the window
	// Set hooks so that the image is modified according to the events

	
	mlx_loop(mlx_res.mlx_id);
	exit(EXIT_SUCCESS);
}
