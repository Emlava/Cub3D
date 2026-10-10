/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:42:54 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/10 21:57:45 by elara-va         ###   ########.fr       */
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

// If freeing line is necessary, use only when another reference to the
// original string is available. It does not ignore a '\n'
void	ignore_white_space(char **line)
{
	while (**line != '\n' && ft_isspace(**line))
		(*line)++;
	return ;
}

void	manage_malloc_failure(t_map_res *map_res, t_map_buff *map_buff)
{
	free_map_buff(map_buff);
	free_map_res(map_res);
	ft_dprintf(2, "malloc() failure\n");
	exit(EXIT_FAILURE);
}
