/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_07.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:08:34 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/20 12:32:55 by kwrzosek         ###   ########.fr       */
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

void	free_map_strings(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->raw_map)
		free(map->raw_map);
	if (map->direction)
		free(map->direction);
}

void	clean_struct(t_map *map)
{
	if (!map)
		return ;
	free_map_strings(map);
	if (map->grid)
		free_split(map->grid);
	if (map->map_copy)
		free_split(map->map_copy);
	free(map);
}

void	*abort_parsing(t_map *map, int fd, int do_drain)
{
	char	*line;

	if (do_drain && fd >= 0)
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	if (fd >= 0)
		close(fd);
	if (map)
		clean_struct(map);
	return (NULL);
}
