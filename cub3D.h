/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:38:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/11/22 11:57:00 by elara-va         ###   ########.fr       */
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
# define PI 3.14159
# define WORLD_SIDE_LENGTH 64
# define PLAYERS_HEIGHT (WORLD_SIDE_LENGTH / 2)
# define FOV 60
# define MALLOC_FAILURE -2

// Things to free/close/destroy
// -mlx_id
// -win;
// -img
// -Everything from map_res
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
	int				ceiling;
	int				floor;
	int				first_line_of_map;
	int				nbr_of_rows;
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
	int				coords[2];
	unsigned int	viewing_angle;
	double			d_to_proj_plane;
	double			angle_between_rays;
	double			ray_angle;
	double			ray_length;
}	t_player_res;

typedef struct s_img
{
	void	*id;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texture
{
	void	*id;
	int		size[2];
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_mlx_resources
{
	void		*mlx_id;
	int			screen_size[2];
	void		*win;
	t_img		img;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
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
t_bool	empty_spaces_in_path(char *path);

// parsing/cleaning.c
void	free_map_res(t_map_res *map_res);
void	free_map_buff(t_map_buff *map_buff);

// prepare_display.c
int		prepare_display(t_mlx_res *mlx_res, t_map_res *map_res);

// rendering/render_frame.c
void	render_frame(t_player_res *player, t_mlx_res *mlx_res,
	t_map_res *map_res);

// rendering/cast_ray.c
void	cast_ray(t_player_res *player, t_map_res *map_res, int col);

// horizontal_intersections.c
void	check_horizontal_intersections(t_player_res *player, t_map_res *map_res,
			double curr_intersection[2]);

// vertical_intersections.c
void	check_vertical_intersections(t_player_res *player, t_map_res *map_res,
			double curr_intersection[2]);

// rendering/ray_utils.c
t_bool	is_inside_the_map(int grid_coords[2], t_map_res *map_res,
			double intersection[2]);
t_bool	wall_check(int grids_coords[2], t_map_res *map_res);
void	define_grid_coords(double intersection[2], int grid_coords[2]);
void	find_wall(double curr_intersection[2], double x_step, double y_step,
			t_map_res *map_res);
	
// cleaning.c
void	destroy_mlx_res(t_mlx_res *mlx_res);
void	clean_and_exit(t_mlx_res *mlx_res, t_map_res *map_res, int exit_status);

#endif
