/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:04:34 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 13:50:00 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_player_count(char **grid)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S' ||
				grid[i][j] == 'E' || grid[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_map_validity(t_map *map)
{
	char	**map_copy;
	int		status;

	if (check_player_count(map->grid) != 1)
	{
		printf("Error\nMap must contain exactly one starting position.\n");
		return (-1);
	}
	get_player_pos(map);
	get_size(map->grid, map);
	map_copy = copy_map(map->grid, map->height);
	if (!map_copy)
		return (-1);
	status = flood_fill(map_copy, map->player_x, map->player_y, map);
	free_split(map_copy);
	return (status);
}

char	*strjoin_with_newline(char *s1, char *s2)
{
	char	*new_str;
	int		len1;
	int		len2;

	if (!s2)
		return (NULL);
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!new_str)
		return (NULL);
	copy_with_newline(new_str, s1, s2);
	return (new_str);
}

int	flood_fill(char **grid, int x, int y, t_map *map)
{
	if (y < 0 || y >= map->height)
		return (-1);
	if (x < 0 || x >= (int)ft_strlen(grid[y]))
		return (-1);
	if (grid[y][x] == ' ')
		return (-1);
	if (grid[y][x] == '\r' || grid[y][x] == '\n')
		return (-1);
	if (grid[y][x] == '1' || grid[y][x] == 'X')
		return (0);
	grid[y][x] = 'X';
	if (flood_fill(grid, x + 1, y, map) == -1)
		return (-1);
	if (flood_fill(grid, x - 1, y, map) == -1)
		return (-1);
	if (flood_fill(grid, x, y + 1, map) == -1)
		return (-1);
	if (flood_fill(grid, x, y - 1, map) == -1)
		return (-1);
	return (0);
}

int	get_player_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				map->player_x = j;
				map->player_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
