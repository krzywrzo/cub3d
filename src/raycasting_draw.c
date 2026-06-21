/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:40:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:46:48 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_background(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		my_pixel_put(&game->frame, x, y, 0x87CEEB);
		y++;
	}
	y = draw_end;
	while (y < HEIGHT)
	{
		my_pixel_put(&game->frame, x, y, 0x228B22);
		y++;
	}
}

void	get_draw_bounds(t_ray_hit *hit, int *draw_start, int *draw_end)
{
	*draw_start = -((int)(HEIGHT / hit->distance)) / 2 + HEIGHT / 2;
	*draw_end = ((int)(HEIGHT / hit->distance)) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

void	init_draw_col(t_game *game, t_ray_hit *hit, t_draw_col *col)
{
	double	wall_x;

	col->tex = pick_texture(game, hit->side, hit->ray_dir_x, hit->ray_dir_y);
	calc_wall_x(game, hit, &wall_x);
	col->tex_x = calc_tex_x(col->tex, wall_x, hit);
}

void	draw_pixels(t_game *game, t_draw_col *col)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	step = (double)col->tex->height / (double)(col->draw_end - col->draw_start);
	tex_pos = (col->draw_start - HEIGHT / 2
			+ (col->draw_end - col->draw_start) / 2) * step;
	y = col->draw_start;
	while (y < col->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= col->tex->height)
			tex_y = col->tex->height - 1;
		my_pixel_put(&game->frame, col->x, y,
			get_texture_color(col->tex, col->tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}

void	draw_pixel_column(t_game *game, t_ray_hit *hit, t_draw_col *col)
{
	init_draw_col(game, hit, col);
	draw_pixels(game, col);
}
