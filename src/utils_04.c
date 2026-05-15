/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_04.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:24:16 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 13:53:53 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

void	free_partial_copy(char **map_cp, int current_index)
{
	while (current_index > 0)
	{
		current_index--;
		free(map_cp[current_index]);
	}
	free(map_cp);
}

char	**copy_map(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	get_size(char **grid, t_map *map)
{
	int		y;
	int		max_width;
	int		current_len;

	y = 0;
	max_width = 0;
	if (!grid || !map)
		return ;
	while (grid[y])
	{
		current_len = ft_strlen(grid[y]);
		if (current_len > max_width)
			max_width = current_len;
		y++;
	}
	map->height = y;
	map->width = max_width;
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
