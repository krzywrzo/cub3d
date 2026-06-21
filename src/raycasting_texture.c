/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:40:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:44:24 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*pick_texture(t_game *game, int side, double ray_x,
		double ray_y)
{
	if (side == 0)
	{
		if (ray_x > 0)
			return (&game->ea);
		return (&game->we);
	}
	if (ray_y > 0)
		return (&game->so);
	return (&game->no);
}

void	calc_wall_x(t_game *game, t_ray_hit *hit, double *wall_x)
{
	if (hit->side == 0)
		*wall_x = game->player->pos_y + hit->distance * hit->ray_dir_y;
	else
		*wall_x = game->player->pos_x + hit->distance * hit->ray_dir_x;
	*wall_x -= floor(*wall_x);
}

int	calc_tex_x(t_texture *tex, double wall_x, t_ray_hit *hit)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if ((hit->side == 0 && hit->ray_dir_x > 0)
		|| (hit->side == 1 && hit->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	set_delta_distances(double ray_x, double ray_y, t_dda *dda)
{
	if (ray_x == 0.0)
		dda->delta_dist[0] = 1e30;
	else
		dda->delta_dist[0] = fabs(1.0 / ray_x);
	if (ray_y == 0.0)
		dda->delta_dist[1] = 1e30;
	else
		dda->delta_dist[1] = fabs(1.0 / ray_y);
}

void	set_hit_distance(t_ray_hit *hit, t_dda *dda)
{
	if (dda->side == 0)
		hit->distance = dda->side_dist[0] - dda->delta_dist[0];
	else
		hit->distance = dda->side_dist[1] - dda->delta_dist[1];
}
