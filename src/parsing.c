/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:10:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/20 17:47:05 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

t_map	*parsing(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	if (argc != 2 || ext_checker(argv[1]) == -1)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCould not open file");
		return (abort_parsing(map, -1, 0));
	}
	if (parse_file_loop(fd, map) == -1 || fc_checker(argv[1]) == -1)
	{
		printf("Error\nWrong floor/ceiling color");
		return (abort_parsing(map, fd, 1));
	}
	close(fd);
	if (validate_parsed_map(map) == -1)
		return (abort_parsing(map, -1, 0));
	return (map);
}

int	parse_file_loop(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, map) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
