/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 19:45:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 19:53:27 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

static int	cleanup_game(t_game *game)
{
	if (!game)
		return (1);
	if (game->player)
		free(game->player);
	if (game->frame.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.img_ptr);
	destroy_textures(game);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	clean_struct(game->map);
	free(game);
	return (1);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pxl / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	close_app(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
	return (0);
}

int	my_mlx_init(t_map *map_info, t_map *raw_map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->map = map_info;
	game->raw_map = raw_map;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (cleanup_game(game));
	game->player = init_player(map_info);
	if (!game->player)
		return (cleanup_game(game));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (cleanup_game(game));
	game->frame.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame.img_ptr)
		return (cleanup_game(game));
	game->frame.addr = mlx_get_data_addr(game->frame.img_ptr,
			&game->frame.bits_per_pxl, &game->frame.line_len,
			&game->frame.endian);
	load_textures(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_app, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	cleanup_game(game);
	return (0);
}