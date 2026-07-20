/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/20 20:11:07 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_char(char *line, int flag)
{
	char	*rgb;
	char	*set;
	char	**rgb_split;

	if (flag == 0)
		set = "F ";
	else
		set = "C ";
	rgb = ft_strtrim(line, set);
	rgb_split = ft_split(rgb, ',');
	if (rgb_split[2] == NULL)
	{
		free_split(rgb_split);
		return (-1);
	}
	if (is_minus(rgb_split) == -1)
	{
		free_split(rgb_split);
		return (-1);
	}
	free_split(rgb_split);
	return (0);
}

int	is_minus(char **rgb)
{
	int	i;
	int	temp;

	i = 0;
	while (rgb[i])
	{
		temp = ft_atoi(rgb[i]);
		if (!(temp >= 0 && temp <= 255))
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map		*map;

	if (argc != 2)
		return (1);
	map = parsing(argc, argv);
	if (!map)
		return (1);
	return (my_mlx_init(map, map));
}
