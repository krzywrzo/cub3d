/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/21 14:12:39 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_char(char *line, int flag)
{
	char	*rgb;
	char	*set;
	char	**rgb_split;

	if (flag == 0)
		set = "F \n";
	else
		set = "C \n";
	rgb = ft_strtrim(line, set);
	if (!rgb)
		return (-1);
	rgb_split = ft_split(rgb, ',');
	free(rgb);
	if (!rgb_split || split_size(rgb_split) != 3 || is_minus(rgb_split) == -1)
	{
		if (rgb_split)
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
	int	k;

	i = 0;
	while (rgb[i])
	{
		if (rgb[i][0] == '\0')
			return (-1);
		k = 0;
		while (rgb[i][k])
		{
			if (ft_isdigit(rgb[i][k]) == 0)
				return (-1);
			k++;
		}
		temp = ft_atoi(rgb[i]);
		if (temp < 0 || temp > 255)
			return (-1);
		i++;
	}
	return (0);
}

// int	is_valid_char(char *line, int flag)
// {
// 	char	*rgb;
// 	char	*set;
// 	char	**rgb_split;

// 	if (flag == 0)
// 		set = "F ";
// 	else
// 		set = "C ";
// 	rgb = ft_strtrim(line, set);
// 	rgb_split = ft_split(rgb, ',');
// 	if (rgb_split[2] == NULL)
// 	{
// 		free(rgb);
// 		free_split(rgb_split);
// 		return (-1);
// 	}
// 	if (is_minus(rgb_split) == -1)
// 	{
// 		free(rgb);
// 		free_split(rgb_split);
// 		return (-1);
// 	}
// 	free(rgb);
// 	free_split(rgb_split);
// 	return (0);
// }

// int	is_minus(char **rgb)
// {
//     int	i;
//     int	temp;
//     int	k;

//     i = 0;
//     while (rgb[i])
//     {
//         if (rgb[i][0] == '\0')
//             return (-1);
//         k = 0;
//         while (rgb[i][k])
//         {
//             if (ft_isdigit(rgb[i][k]) == 0)
//                 return (-1);
//             k++;
//         }
//         temp = ft_atoi(rgb[i]);
//         if (temp < 0 || temp > 255)
//             return (-1);
//         i++;
//     }
//     return (0);
// }

// int	is_minus(char **rgb)
// {
// 	int	i;
// 	int	temp;
// 	int	k;

// 	i = 0;
// 	while (rgb[i])
// 	{
// 		k = 0;
// 		while (rgb[i][k])
// 		{
// 			if (ft_isdigit(rgb[i][k]) == 1)
// 				return (-1);
// 			k++;
// 		}
// 		temp = ft_atoi(rgb[i]);
// 		printf("%d\n", temp);
// 		if (!(temp >= 0 && temp <= 255))
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_map		*map;

	if (argc != 2)
	{
		ft_printf("Error\nNo map provided\n");
		return (1);
	}
	map = parsing(argc, argv);
	if (!map)
		return (1);
	return (my_mlx_init(map, map));
}
