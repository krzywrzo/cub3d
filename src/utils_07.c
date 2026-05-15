/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_07.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:08:34 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 14:10:19 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_fc_line(t_fc *fc, char *line)
{
	if (ft_strlcmp(line, "F", 1) == 0)
	{
		if (fc->f != NULL)
			return (1);
		fc->f = ft_strdup(line);
	}
	else if (ft_strlcmp(line, "C", 1) == 0)
	{
		if (fc->c != NULL)
			return (1);
		fc->c = ft_strdup(line);
	}
	return (0);
}

int	loop_fc(int fd, t_fc *fc)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strlen(line) > 0)
	{
		if (check_fc_line(fc, line) == 1)
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}
