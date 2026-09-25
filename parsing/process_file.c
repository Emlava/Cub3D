/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:43:37 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/25 12:45:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	skip_empty_space(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
	return ;
}

int	store_texture_or_color(char *line, t_map_res *map_res) // LEFT OFF HERE
{
	int	i;

	i = 0;
	skip_empty_space(line, &i);
	line += i;
	if (!(*line))
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
	{
		i = 3;
		skip_empty_space(line, &i);
		line += i;
		if (!(*line))
			return (-1);
		map_res->north = ft_strdup(line); // If malloc() fails here, the program will exit when checking for missing fields
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
	{}
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
	{}
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
	{}
	else if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]))
	{}
	else if (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
	{}
	else
		return (-1);
}

t_bool	missing_field(t_map_res *map_res)
{
	if (!map_res->north || !map_res->south || !map_res->east
		|| !map_res->west || map_res->ceiling[0] == -1 || map_res->floor[0] == -1)
		return (TRUE);
	return (FALSE);
}

void	process_textures_and_colors(char **line, t_map_res *map_res,
	int *line_count, int fd)
{
	while (*line && line_is_not_map(*line))
	{
		if (store_texture_or_color(*line, map_res) == -1) //
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

void	process_map(char *line, t_map_res *map_res, int line_count, int fd)
{
}

void	store_file_info(int fd, t_map_res *map_res)
{
	char	*line;
	int		line_count;

	line = get_next_line(fd);
	line_count = 1;
	process_textures_and_colors(&line, map_res, &line_count, fd);

	// Put in process_map()
	while (line)
	{
		if (store_map_row(line, map_res) == -1) //
		{
			ft_dprintf(2, "Error\nLine %d of the given file is invalid\n",
				line_count);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	//
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
