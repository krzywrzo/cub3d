/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:01:27 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/04 02:07:43 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_info_print(t_map_info *map_info)
{

	int i = 0;
	while (map_info->map_copy[i])
	{
		printf("%s\n", map_info->map_copy[i]);
		i++;
	}
	printf("Player pos: [x] = %i [y] = %i\n", map_info->player_x, map_info->player_y);
	printf("Map size: [width] = %i [heigth] = %i", map_info->map_width, map_info->map_height);
}

t_map_info *struct_filler(t_map *map)
{
	t_map_info *map_info;

	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (NULL);
	map_info->map_copy = ft_split(map->one_line_map, 10);
	if (!map_info->map_copy)
	{
		free(map_info);
		return (NULL);
	}
	get_pos(map_info->map_copy, map_info);
	get_size(map_info->map_copy, map_info);
	//map_info->direction = map->map[map_info->player_x][map_info->player_y];
	map_info->direction = map_info->map_copy[map_info->player_y][map_info->player_x];
	return(map_info);
}

void	get_size(char **map, t_map_info *map_info)
{
    int longest_line;
    int current_len;
    int i;

    longest_line = 0;
    i = 0;
    while (map[i])
    {
        current_len = ft_strlen(map[i]);
        if (current_len > longest_line)
            longest_line = current_len;
        i++;
    }
	map_info->map_width = longest_line;
	map_info->map_height = i;
}

void get_pos(char **map, t_map_info *map_info)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1')
			{
				map_info->player_x = j;
				map_info->player_y = i;
				break;
			}
			j++;
		}
		i++;
	}
}