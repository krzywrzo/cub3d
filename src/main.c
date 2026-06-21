/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/06/21 17:53:46 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map		*map;
	t_map_info	*map_info;

	if (argc != 2)
		return (1);
	map = parser(argv);
	if (!map)
		return (1);
	map_info = struct_filler(map);
	if (!map_info)
	{
		free_map(map);
		return (1);
	}
	my_mlx_init(map_info, map);
	free_map(map);
	return (0);
}
