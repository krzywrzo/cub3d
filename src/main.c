/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/04/08 16:31:33 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_map_info	*map_info;

	map = parser(argv);
	if (!map)
		return (1);
	map_info = struct_filler(map);
	if (!map_info)
	{
		free_map(map);
		return (1);
	}
	my_mlx_init(map_info);
	free_map(map);
	return (0);
}
