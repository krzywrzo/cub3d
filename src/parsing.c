/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:45:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/01/24 20:23:36 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_parse(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error with opening file");
		return(handle_error());
	}
	// printf("[DEBUG]: map_parse\n");
	handle_file(fd);
	close(fd);
	return (0);
}

void	handle_file(int fd)
{
	char	*line;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		handle_error();
	// printf("[DEBUG]: handle_file - after struct malloc\n");
	while (line = get_next_line(fd))
	{
		// printf("[DEBUG]: handle_file - while\n");
		handle_line(map, line);
		// printf("line: %s\n", line);
	}
	print_struct(map);
}

//	FIX: add proper file structure checking
void	handle_line(t_map *map, char *line)
{
	if (ft_strlcmp(line, "NO", 2) == 0)
		ft_strlcpy(map->no, line, ft_strlen(line));
	else if (ft_strlcmp(line, "SO", 2) == 0)
		ft_strlcpy(map->so, line, ft_strlen(line));
	else if (ft_strlcmp(line, "WE", 2) == 0)
		ft_strlcpy(map->we, line, ft_strlen(line));
	else if (ft_strlcmp(line, "EA", 2) == 0)
		ft_strlcpy(map->ea, line, ft_strlen(line));
	else if (line[0] == '1')
		ft_strlcat(map->one_line_map, line, ft_strlen(line));
}

void	print_struct(t_map *map)
{
	printf("%s\n", map->no);
	printf("%s\n", map->so);
	printf("%s\n", map->we);
	printf("%s\n", map->ea);
}

char	space_to_zero (char s)
{
	if (s == ' ')
		return ('0');
	return (s);
}
