/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_06.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:56:02 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/06/21 19:25:54 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_parsed_map(t_map *map)
{
	map->grid = ft_split(map->raw_map, '\n');
	if (!map->grid)
	{
		printf("grid is empty");
		return (-1);
	}
	get_size(map->grid, map);
	if (get_player_pos(map) == -1)
	{
		printf("Player not found\n");
		return (-1);
	}
	if (check_player_count(map->grid) != 1)
	{
		printf("Error\nMap must contain exactly one starting position.\n");
		return (-1);
	}
	if (check_map_validity(map) == -1)
	{
		printf("Error\nMap is not enclosed by walls.\n");
		return (-1);
	}
	return (0);
}

int	process_line(char *line, t_map *map)
{
	if (is_empty_line(line))
		return (0);
	if (!all_elements_found(map))
		return (parse_texture_or_color(line, map));
	return (extract_map_line(line, map));
}

int	check_texture(t_tex *tex, char *line)
{
	if (ft_strlcmp(line, "NO", 2) == 0)
	{
		if (tex->no != NULL)
			return (1);
		tex->no = ft_strdup(line);
	}
	else if (ft_strlcmp(line, "SO", 2) == 0)
	{
		if (tex->so != NULL)
			return (1);
		tex->so = ft_strdup(line);
	}
	else if (ft_strlcmp(line, "WE", 2) == 0)
	{
		if (tex->we != NULL)
			return (1);
		tex->we = ft_strdup(line);
	}
	else if (ft_strlcmp(line, "EA", 2) == 0)
	{
		if (tex->ea != NULL)
			return (1);
		tex->ea = ft_strdup(line);
	}
	return (0);
}

int	check_line_garbage(char *line)
{
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (!splitted)
		return (-1);
	if (split_size(splitted) != 2)
	{
		free_split(splitted);
		return (-1);
	}
	free_split(splitted);
	return (0);
}
