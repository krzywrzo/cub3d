/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:40:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:46:48 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_ray_direction(t_game *game, int x, double *ray_dir_x,
		double *ray_dir_y)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	*ray_dir_x = game->player->view_dir_x + game->player->plane_x * camera_x;
	*ray_dir_y = game->player->view_dir_y + game->player->plane_y * camera_x;
}

t_ray_hit	*cast_ray(t_game *game, double ray_dir_x, double ray_dir_y)
{
	t_ray_hit	*hit;
	t_dda		dda;

	hit = malloc(sizeof(t_ray_hit));
	if (!hit)
		return (NULL);
	dda_init(game, &dda);
	set_delta_distances(ray_dir_x, ray_dir_y, &dda);
	dda_step_x(game, ray_dir_x, &dda);
	dda_step_y(game, ray_dir_y, &dda);
	dda.side_dist[2] = dda.delta_dist[0];
	dda.side_dist[3] = dda.delta_dist[1];
	dda_loop(game, &dda);
	set_hit_distance(hit, &dda);
	hit->side = dda.side;
	hit->ray_dir_x = ray_dir_x;
	hit->ray_dir_y = ray_dir_y;
	return (hit);
}

void	render_column(t_game *game, int x)
{
	double		ray_dir_x;
	double		ray_dir_y;
	t_ray_hit	*hit;
	t_draw_col	col;

	get_ray_direction(game, x, &ray_dir_x, &ray_dir_y);
	hit = cast_ray(game, ray_dir_x, ray_dir_y);
	if (!hit)
		return ;
	col.x = x;
	get_draw_bounds(hit, &col.draw_start, &col.draw_end);
	fill_background(game, x, col.draw_start, col.draw_end);
	draw_pixel_column(game, hit, &col);
	free(hit);
}

void	render_scene(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		render_column(game, x);
		x++;
	}
}
