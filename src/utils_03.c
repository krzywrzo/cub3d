/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:29:27 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 14:11:55 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	extract_map_line(char *line, t_map *map)
{
	char	*temp;

	if (!is_valid_map_line(line))
	{
		printf("Error\nInvalid character found in map.\n");
		return (-1);
	}
	if (map->raw_map == NULL)
	{
		map->raw_map = ft_strdup(line);
	}
	else
	{
		temp = ft_strjoin(map->raw_map, line);
		free(map->raw_map);
		map->raw_map = temp;
	}
	return (0);
}

int	is_dups(int fd)
{
	t_tex	*tex;
	char	*line;

	tex = ft_calloc(1, sizeof(t_tex));
	if (!tex)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_texture(tex, line) == 1)
		{
			free(line);
			return (free_tex(tex, 1));
		}
		free(line);
		line = get_next_line(fd);
	}
	return (free_tex(tex, 0));
}

int	ext_checker(char *filename)
{
	char	**file_split;

	file_split = ft_split(filename, '.');
	if (!file_split[1])
	{
		free_split(file_split);
		return (-1);
	}
	if (ft_strncmp(file_split[1], "cub", 3) != 0)
	{
		printf("Wrong file extension %s\n", file_split[1]);
		free_split(file_split);
		return (-1);
	}
	if (file_split[2])
	{
		free_split(file_split);
		return (-1);
	}
	free_split(file_split);
	return (0);
}

int	get_map_size(char **map, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		i++;
		while (map[i][j])
			j++;
	}
	if (flag == 0)
		return (i);
	else
		return (j);
}
