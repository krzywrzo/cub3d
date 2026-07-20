/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/07/20 20:11:39 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_rgb(char *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		c;

	rgb = ft_split(color, ',');
	if (!rgb || split_size(rgb) != 3)
	{
		if (rgb)
			free_split(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	c = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (c);
}

int	is_wall(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x <= 0 || map_y <= 0 || map_y >= map->height)
		return (1);
	if (map_x >= (int)ft_strlen(map->map_copy[map_y]))
		return (1);
	if (map->map_copy[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		game->keys.esc = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
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
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
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
