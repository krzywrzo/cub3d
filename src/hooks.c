/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:49:42 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		game->keys.esc = 1;
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		game->keys.esc = 0;
	else if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	return (0);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->keys.esc)
		close_app(game);
	handle_movement(game);
	render_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img_ptr, 0, 0);
	return (0);
}
