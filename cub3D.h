/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:38:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/24 12:50:57 by elara-va         ###   ########.fr       */
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

typedef int	t_bool;

typedef struct s_map_resources
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned char	floor[3];
	unsigned char	ceiling[3];
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

#endif
