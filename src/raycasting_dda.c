/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:40:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:44:24 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda_init(t_game *game, t_dda *dda)
{
	dda->map_xy[0] = (int)game->player->pos_x;
	dda->map_xy[1] = (int)game->player->pos_y;
}

void	dda_step_x(t_game *game, double ray_x, t_dda *dda)
{
	if (ray_x < 0)
	{
		dda->step[0] = -1;
		dda->side_dist[0] = (game->player->pos_x - dda->map_xy[0])
			* dda->delta_dist[0];
	}
	else
	{
		dda->step[0] = 1;
		dda->side_dist[0] = (dda->map_xy[0] + 1.0 - game->player->pos_x)
			* dda->delta_dist[0];
	}
}

void	dda_step_y(t_game *game, double ray_y, t_dda *dda)
{
	if (ray_y < 0)
	{
		dda->step[1] = -1;
		dda->side_dist[1] = (game->player->pos_y - dda->map_xy[1])
			* dda->delta_dist[1];
	}
	else
	{
		dda->step[1] = 1;
		dda->side_dist[1] = (dda->map_xy[1] + 1.0 - game->player->pos_y)
			* dda->delta_dist[1];
	}
}

int	is_wall_hit(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_y >= game->map->map_height)
		return (1);
	if (map_x >= (int)ft_strlen(game->map->map_copy[map_y]))
		return (1);
	if (game->map->map_copy[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	dda_loop(t_game *game, t_dda *dda)
{
	while (1)
	{
		if (dda->side_dist[0] < dda->side_dist[1])
		{
			dda->side_dist[0] += (dda->side_dist[2]);
			dda->map_xy[0] += dda->step[0];
			dda->side = 0;
		}
		else
		{
			dda->side_dist[1] += (dda->side_dist[3]);
			dda->map_xy[1] += dda->step[1];
			dda->side = 1;
		}
		if (is_wall_hit(game, dda->map_xy[0], dda->map_xy[1]))
			break ;
	}
}
