/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/07/20 17:46:41 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
