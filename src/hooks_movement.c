/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:50:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:49:42 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.04

int	is_wall(t_map_info *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= map->map_height)
		return (1);
	if (map_x >= (int)ft_strlen(map->map_copy[map_y]))
		return (1);
	if (map->map_copy[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	check_and_move_x(t_game *game, double move_x)
{
	if (!is_wall(game->map, game->player->pos_x + move_x,
			game->player->pos_y))
		game->player->pos_x += move_x;
}

void	check_and_move_y(t_game *game, double move_y)
{
	if (!is_wall(game->map, game->player->pos_x,
			game->player->pos_y + move_y))
		game->player->pos_y += move_y;
}

void	rotate_player(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->view_dir_x;
	p->view_dir_x = p->view_dir_x * cos(rot) - p->view_dir_y * sin(rot);
	p->view_dir_y = old_dir_x * sin(rot) + p->view_dir_y * cos(rot);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

void	handle_movement(t_game *game)
{
	if (game->keys.w)
	{
		check_and_move_x(game, game->player->view_dir_x * MOVE_SPEED);
		check_and_move_y(game, game->player->view_dir_y * MOVE_SPEED);
	}
	if (game->keys.s)
	{
		check_and_move_x(game, -game->player->view_dir_x * MOVE_SPEED);
		check_and_move_y(game, -game->player->view_dir_y * MOVE_SPEED);
	}
	if (game->keys.a)
		rotate_player(game->player, -ROT_SPEED);
	if (game->keys.d)
		rotate_player(game->player, ROT_SPEED);
}
