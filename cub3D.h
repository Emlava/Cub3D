/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:38:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/12 19:30:53 by elara-va         ###   ########.fr       */
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

# define FALSE 0
# define TRUE 1
# define X 0
# define Y 1
# define PLAYERS_HEIGHT 32
# define WORLDS_SIDE_LENGTH 64
# define FOV 60
# define MALLOC_FAILURE -2

// Things to free/close/destroy
// -mlx_id
// -win;
// -img
// -Everything from map_res;
// -fd
// -line
// -map_buff nodes (not the row variables)

typedef int	t_bool;

typedef struct s_map_resources
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				ceiling[3];
	int				floor[3];
	t_bool			ceiling_is_set;
	t_bool			floor_is_set;
	int				first_line_of_map;
	int				nbr_of_rows; // Empty lines
	size_t			size_of_longest_row;
	char			**map;
}	t_map_res;

typedef struct s_map_buff
{
	char				*row;
	struct s_map_buff	*next;
}	t_map_buff;

typedef struct s_player_resources
{
	int	coords[2];
	int	viewing_angle;
}	t_player_res;

typedef struct s_mlx_resources
{
	void	*mlx_id;
	int		screen_size[2];
	void	*win;
	void	*img;
}	t_mlx_res;

// parsing/process_file.c
void	process_file(int ac, char *av[], t_map_res *map_res,
			t_player_res *player);

// parsing/store_textures_and_colors.c
void	store_textures_and_colors(char **line, t_map_res *map_res,
			int *line_count, int fd);

// parsing/get_fields.c
int		get_meridian_texture(char *line, t_map_res *map_res, char *direction);
int		get_parallel_texture(char *line, t_map_res *map_res, char *direction);
int		get_color(char *line, t_map_res *map_res, char c);

// parsing/store_map.c
void	store_map(char *line, t_map_res *map_res, int fd);

// parsing/parse_map.c
void	parse_map(t_map_res *map_res, t_player_res *player);

// parsing/map_utils.c
void	manage_malloc_failure(t_map_res *map_res, t_map_buff *map_buff);
t_bool	orthogonal_space(char **map, int x, int y);
t_bool	row_is_empty(char *line);
void	check_player_is_present(int player_coord_x, t_map_res *map_res);
void	remove_trailing_empty_rows(t_map_res *map_res, int y);

// parsing/field_utils.c
t_bool	line_is_not_map(char *line);
void	ignore_white_space(char **line);

// cleaning.c
void	free_map_res(t_map_res *map_res);
void	free_map_buff(t_map_buff *map_buff);

#endif
