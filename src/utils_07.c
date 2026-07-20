/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_07.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:08:34 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/20 17:37:31 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_minus(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '-')
			return (-1);
		i++;
	}
	return (0);
}

int	check_fc_line(t_fc *fc, char *line)
{
	if (ft_strlcmp(line, "F ", 2) == 0 || ft_strlcmp(line, "F\t", 2) == 0)
	{
		if (fc->f != NULL || check_line_garbage(line) == -1)
			return (-1);
		if (is_minus(line) == -1)
			return (-1);
		fc->f = ft_strdup(line);
	}
	else if (ft_strlcmp(line, "C ", 2) == 0 || ft_strlcmp(line, "C\t", 2) == 0)
	{
		if (fc->c != NULL || check_line_garbage(line) == -1)
			return (-1);
		if (is_minus(line) == -1)
			return (-1);
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
		if (check_fc_line(fc, line) == -1)
		{
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}
