/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:52:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/02/04 19:23:54 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_correct(t_map *map)
{
	t_map_info	*map_info;

	map_info = struct_filler(map);
	if (!map_info)
		return (-1);
	if (flood_fill(map_info, map_info->player_x, map_info->player_y) == 0)
	{	
		printf("Map is correct\n");
		// free_struct(map_info);	// TODO: free_struct()
		return (0);
	}
	else
	{
		printf("Map is incorrect\n");
		// free_struct(map_info);
		return (1);
	}
	return (0);
}

int flood_fill(t_map_info *map_info, int x, int y)
{
	char	c;

	if (y < 0 || y >= map_info->map_height || x < 0 || x >= map_info->map_width)
		return (-1);
	c = map_info->map_copy[y][x];
	if (c == '1' || c == 'X')
		return (0);
	if (c == ' ')
		return (-1);
	map_info->map_copy[y][x] = 'X';
	if (flood_fill(map_info, x + 1, y) == -1)
        return (-1);
    if (flood_fill(map_info, x - 1, y) == -1)
        return (-1);
    if (flood_fill(map_info, x, y + 1) == -1)
        return (-1);
    if (flood_fill(map_info, x, y - 1) == -1)
        return (-1);
	return (0);
}
