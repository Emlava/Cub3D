/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:38:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/25 18:37:14 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

# define FALSE 0
# define TRUE 1

typedef int	t_bool;

typedef struct s_map_resources
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor[3];
	int 			ceiling[3];
	char			**map;
}	t_map_res;

typedef struct s_mlx_resources
{
	void	*mlx_id;
	int		size_x;
	int		size_y;
	void	*win;
	void	*img;
}	t_mlx_res;

// parsing/process_file.c
int		store_field(char *line, t_map_res *map_res);
void	store_textures_and_colors(char **line, t_map_res *map_res,
			int *line_count, int fd);
void	store_map(char *line, t_map_res *map_res, int line_count, int fd);
void	store_file_info(int fd, t_map_res *map_res);
void	process_file(int ac, char *av[], t_map_res *map_res);

// parsing/utils.c
t_bool	file_extension_check(char *file);
void	ignore_leading_white_space(char **line);
t_bool	missing_field(t_map_res *map_res);


// cleaning.c
void	free_map_res(t_map_res *map_res);

#endif
