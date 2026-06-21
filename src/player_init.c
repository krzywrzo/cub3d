/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:50:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:49:42 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_dir(t_player *player, t_map_info *map)
{
	if (map->direction == 'N')
	{
		player->view_dir_x = 0;
		player->view_dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (map->direction == 'S')
	{
		player->view_dir_x = 0;
		player->view_dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (map->direction == 'E')
	{
		player->view_dir_x = 1;
		player->view_dir_y = 0;
		player->plane_y = 0.66;
	}
	else if (map->direction == 'W')
	{
		player->view_dir_x = -1;
		player->view_dir_y = 0;
		player->plane_y = -0.66;
	}
}

t_player	*init_player(t_map_info *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = (double)map->player_x + 0.5;
	player->pos_y = (double)map->player_y + 0.5;
	player->view_dir_x = 0;
	player->view_dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player_dir(player, map);
	return (player);
}

void	destroy_textures(t_game *game)
{
	if (game->no.img)
		mlx_destroy_image(game->mlx, game->no.img);
	if (game->so.img)
		mlx_destroy_image(game->mlx, game->so.img);
	if (game->we.img)
		mlx_destroy_image(game->mlx, game->we.img);
	if (game->ea.img)
		mlx_destroy_image(game->mlx, game->ea.img);
}
