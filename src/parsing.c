/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:45:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/01/24 18:28:54 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	map_parse(char *map_path)
// {
// 	int	fd;

// 	fd = open(map_path, O_WRONLY);
// 	if (fd == -1)
// 		return(handle_error());
// 	handle_file(fd);
// 	return (0);
// }

// void	handle_file(int fd)
// {
// 	char	*line;
// 	t_map	*map;

// 	map = malloc(sizeof(t_map));
// 	if (!map)
// 		handle_error();
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		handle_line(map, line);
// 	}
// }

// void	handle_line(t_map *map, char *line)
// {

// }

// char	space_to_zero (char s)
// {
// 	if (s == ' ')
// 		return ('0');
// }
