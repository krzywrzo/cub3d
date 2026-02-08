/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:45:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/02/08 15:50:54 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*map_parse(char *map_path)
{
	int		fd;
	t_map	*map;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error with opening file");
		handle_error();
		return (NULL);
	}
	map = handle_file(fd);
	close(fd);
	map->map = ft_split(map->one_line_map, 10);
	if (!map->map)
	{
		free_map(map);
		handle_error();
	}
	return (map);
}

t_map	*handle_file(int fd)
{
	char	*line;
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		handle_error();
	while ((line = get_next_line(fd)))
	{
		handle_line(map, line);
		free(line);
	}
	return (map);
}

//	FIX: add proper file structure checking
void	handle_line(t_map *map, char *line)
{
	char	*temp;

	if (ft_strlcmp(line, "NO", 2) == 0)
		map->no = ft_strdup(line);
	else if (ft_strlcmp(line, "SO", 2) == 0)
		map->so = ft_strdup(line);
	else if (ft_strlcmp(line, "WE", 2) == 0)
		map->we = ft_strdup(line);
	else if (ft_strlcmp(line, "EA", 2) == 0)
		map->ea = ft_strdup(line);
	else if (line[0] == '1' || line[0] == '0')
	{
		temp = map->one_line_map;
		if (!temp)
			map->one_line_map = ft_strdup(line);
		else
		{
			map->one_line_map = ft_strjoin(temp, line);
			free(temp);
		}
	}
}
