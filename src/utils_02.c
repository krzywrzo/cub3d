/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:22:24 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 13:53:40 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	all_elements_found(t_map *map)
{
	if (map->no && map->so && map->we && map->ea && map->f && map->c)
		return (1);
	return (0);
}

int	assign_element(char **target, char *data)
{
	if (*target != NULL)
	{
		printf("Error\nDuplicate element found.\n");
		return (-1);
	}
	*target = ft_strdup(data);
	return (0);
}

int	parse_texture_or_color(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		return (assign_element(&map->no, line + i + 3));
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		return (assign_element(&map->so, line + i + 3));
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		return (assign_element(&map->we, line + i + 3));
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		return (assign_element(&map->ea, line + i + 3));
	else if (ft_strncmp(line + i, "F ", 2) == 0)
		return (assign_element(&map->f, line + i + 2));
	else if (ft_strncmp(line + i, "C ", 2) == 0)
		return (assign_element(&map->c, line + i + 2));
	printf("Error\nInvalid or unrecognized element before map: %s\n", line);
	return (-1);
}

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW\n\r", line[i]))
		{
			printf("Error\nMap rejected! Found illegal character\n");
			return (0);
		}
		i++;
	}
	return (1);
}
