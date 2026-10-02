/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:38:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/02 11:53:36 by elara-va         ###   ########.fr       */
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
# define X 0
# define Y 1
# define PLAYERS_HEIGHT 32
# define WORLDS_SIDE_LENGTH 64
# define FOV 60

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
	int 			ceiling[3];
	int				floor[3];
	t_bool			ceiling_is_set;
	t_bool			floor_is_set;
	int				first_line_of_map;
	int				nbr_of_rows;
	char			**map;
}	t_map_res;

typedef struct s_map_buff
{
	char				*row;
	struct s_map_buff	*next;
}	t_map_buff;

typedef struct s_player_resources
{
	int		coords[2];
	float	viewing_angle;
}	t_player_res;

typedef struct s_mlx_resources
{
	void	*mlx_id;
	int		screen_size[2];
	void	*win;
	void	*img;
}	t_mlx_res;

// parsing/process_file.c
void	process_file(int ac, char *av[], t_map_res *map_res, t_player_res *player);

// parsing/store_textures_and_colors.c
void	store_textures_and_colors(char **line, t_map_res *map_res,
			int *line_count, int fd);

// parsing/field_utils.c
int	get_north_texture(char *line, t_map_res *map_res);
int	get_south_texture(char *line, t_map_res *map_res);
int	get_east_texture(char *line, t_map_res *map_res);
int	get_west_texture(char *line, t_map_res *map_res);
int	get_color(char *line, t_map_res *map_res, char c);

// parsing/store_map.c
void	store_map(char *line, t_map_res *map_res, int fd);

// parsing/parse_map.c
void	parse_map(t_map_res *map_res, t_player_res *player);

// parsing/utils.c
t_bool	file_extension_check(char *file);
void	ignore_leading_white_space(char **line);
t_bool	line_is_not_empty(char *line);

// cleaning.c
void	free_map_res(t_map_res *map_res);
void	free_map_buff(t_map_buff *map_buff);

#endif
