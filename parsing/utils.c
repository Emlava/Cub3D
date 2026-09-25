/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:42:54 by elara-va          #+#    #+#             */
/*   Updated: 2026/09/25 18:09:56 by elara-va         ###   ########.fr       */
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

// Only use when another reference to the original string is available
// if needed to free
void	ignore_leading_white_space(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	return ;
}

t_bool	missing_field(t_map_res *map_res)
{
	if (!map_res->north || !map_res->south || !map_res->east
		|| !map_res->west || map_res->ceiling[0] == -1 || map_res->floor[0] == -1)
		return (TRUE);
	return (FALSE);
}

