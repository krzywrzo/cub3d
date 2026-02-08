/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/02/08 15:50:41 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main (int argc, char **argv)
{
	char	*map_path;
	t_map	*map;

	if (argc != 2)
		return (1);
	map = map_parse(argv[1]);
	if (!map)
		return(handle_error());	//	TODO: handle_error()
	// print_struct(map);
	is_map_correct(map);	// TODO: flood_fill()
	free_map(map);
	return (0);
}

// int	close_app(void *param)
// {
// 	t_cub *cub;

// 	cub = (t_cub *)param;
// 	if (cub->win)
// 		mlx_destroy_window(cub->mlx, cub->win);
// 	mlx_destroy_display(cub->mlx);
// 	free(cub->mlx);
// 	exit(0);
// 	return (0);
// }

// int	main(void)
// {
// 	t_cub cub;

// 	cub.mlx = mlx_init();
// 	if (!cub.mlx)
// 		return (1);
// 	cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "cwel");
// 	if (!cub.win)
// 		return (1);
// 	mlx_hook(cub.win, 17, 0, close_app, &cub);
// 	mlx_loop(cub.mlx);
// 	return (0);
// }
