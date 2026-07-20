/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_07.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:08:34 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/20 18:40:32 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
