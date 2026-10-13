/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 18:50:20 by elara-va          #+#    #+#             */
/*   Updated: 2026/10/13 19:30:24 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static t_bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (TRUE);
	return (FALSE);
}

t_bool	line_is_not_map(char *line)
{
	if (is_map_char(*line))
	{
		line++;
		while (is_map_char(*line))
			line++;
		if (!*line || *line == '\n')
			return (FALSE);
	}
	return (TRUE);
}

// If freeing line is necessary, use only when another reference to the
// original string is available. It does not ignore a '\n'
void	ignore_white_space(char **line)
{
	while (**line != '\n' && ft_isspace(**line))
		(*line)++;
	return ;
}
