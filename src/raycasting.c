/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 16:29:41 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_background(t_game *game, int x, int draw_start, int draw_end)
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

static t_texture	*pick_texture(t_game *game, int side, double ray_dir_x,
        double ray_dir_y)
{
    if (side == 0)
    {
        if (ray_dir_x > 0)
            return (&game->ea);
        return (&game->we);
    }
    if (ray_dir_y > 0)
        return (&game->so);
    return (&game->no);
}

static void	calc_wall_x(t_game *game, t_ray_hit *hit, double *wall_x)
{
    if (hit->side == 0)
        *wall_x = game->player->pos_y + hit->distance * hit->ray_dir_y;
    else
        *wall_x = game->player->pos_x + hit->distance * hit->ray_dir_x;
    *wall_x -= floor(*wall_x);
}

static int	calc_tex_x(t_texture *tex, double wall_x, t_ray_hit *hit)
{
    int	tex_x;

    tex_x = (int)(wall_x * (double)tex->width);
    if ((hit->side == 0 && hit->ray_dir_x > 0)
        || (hit->side == 1 && hit->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    return (tex_x);
}

static void	init_draw_col(t_game *game, t_ray_hit *hit, t_draw_col *col)
{
    double	wall_x;

    col->tex = pick_texture(game, hit->side, hit->ray_dir_x, hit->ray_dir_y);
    calc_wall_x(game, hit, &wall_x);
    col->tex_x = calc_tex_x(col->tex, wall_x, hit);
}

static void	draw_pixels(t_game *game, t_draw_col *col)
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

static void	draw_pixel_column(t_game *game, t_ray_hit *hit, int x,
        int draw_start, int draw_end)
{
    t_draw_col	col;

    col.x = x;
    col.draw_start = draw_start;
    col.draw_end = draw_end;
    init_draw_col(game, hit, &col);
    draw_pixels(game, &col);
}

static void	get_draw_bounds(t_ray_hit *hit, int *draw_start, int *draw_end)
{
    *draw_start = -((int)(HEIGHT / hit->distance)) / 2 + HEIGHT / 2;
    *draw_end = ((int)(HEIGHT / hit->distance)) / 2 + HEIGHT / 2;
    if (*draw_start < 0)
        *draw_start = 0;
    if (*draw_end >= HEIGHT)
        *draw_end = HEIGHT - 1;
}

static void	get_ray_direction(t_game *game, int x, double *ray_dir_x,
        double *ray_dir_y)
{
    double	camera_x;

    camera_x = 2.0 * x / (double)WIDTH - 1.0;
    *ray_dir_x = game->player->view_dir_x + game->player->plane_x * camera_x;
    *ray_dir_y = game->player->view_dir_y + game->player->plane_y * camera_x;
}

static void	dda_init(t_game *game, int *map_xy)
{
    map_xy[0] = (int)game->player->pos_x;
    map_xy[1] = (int)game->player->pos_y;
}

static void	dda_step_x(t_game *game, double ray_x, double delta_x,
        double *side_dist_x, int *step_x, int map_x)
{
    if (ray_x < 0)
    {
        *step_x = -1;
        *side_dist_x = (game->player->pos_x - map_x) * delta_x;
    }
    else
    {
        *step_x = 1;
        *side_dist_x = (map_x + 1.0 - game->player->pos_x) * delta_x;
    }
}

static void	dda_step_y(t_game *game, double ray_y, double delta_y,
        double *side_dist_y, int *step_y, int map_y)
{
    if (ray_y < 0)
    {
        *step_y = -1;
        *side_dist_y = (game->player->pos_y - map_y) * delta_y;
    }
    else
    {
        *step_y = 1;
        *side_dist_y = (map_y + 1.0 - game->player->pos_y) * delta_y;
    }
}

static int	is_wall_hit(t_game *game, int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0 || map_y >= game->map->map_height)
        return (1);
    if (map_x >= (int)ft_strlen(game->map->map_copy[map_y]))
        return (1);
    if (game->map->map_copy[map_y][map_x] == '1')
        return (1);
    return (0);
}

static void	dda_loop(t_game *game, int *map_xy, double *side_dist,
        int *step, int *side)
{
    while (1)
    {
        if (side_dist[0] < side_dist[1])
        {
            side_dist[0] += (side_dist[2]);
            map_xy[0] += step[0];
            *side = 0;
        }
        else
        {
            side_dist[1] += (side_dist[3]);
            map_xy[1] += step[1];
            *side = 1;
        }
        if (is_wall_hit(game, map_xy[0], map_xy[1]))
            break ;
    }
}

static void	set_delta_distances(double ray_x, double ray_y, double *delta_x,
        double *delta_y)
{
    if (ray_x == 0.0)
        *delta_x = 1e30;
    else
        *delta_x = fabs(1.0 / ray_x);
    if (ray_y == 0.0)
        *delta_y = 1e30;
    else
        *delta_y = fabs(1.0 / ray_y);
}

static void	set_hit_distance(t_ray_hit *hit, int side, double dist_x,
        double dist_y, double delta_x, double delta_y)
{
    if (side == 0)
        hit->distance = dist_x - delta_x;
    else
        hit->distance = dist_y - delta_y;
}

static t_ray_hit	*cast_ray(t_game *game, double ray_dir_x, double ray_dir_y)
{
    t_ray_hit	*hit;
    int			map_xy[2];
    double		delta_dist[2];
    double		side_dist[4];
    int			step[2];
    int			side;

    hit = malloc(sizeof(t_ray_hit));
    if (!hit)
        return (NULL);
    dda_init(game, map_xy);
    set_delta_distances(ray_dir_x, ray_dir_y, &delta_dist[0], &delta_dist[1]);
    dda_step_x(game, ray_dir_x, delta_dist[0], &side_dist[0], &step[0],
        map_xy[0]);
    dda_step_y(game, ray_dir_y, delta_dist[1], &side_dist[1], &step[1],
        map_xy[1]);
    side_dist[2] = delta_dist[0];
    side_dist[3] = delta_dist[1];
    dda_loop(game, map_xy, side_dist, step, &side);
    set_hit_distance(hit, side, side_dist[0], side_dist[1],
        delta_dist[0], delta_dist[1]);
    hit->side = side;
    hit->ray_dir_x = ray_dir_x;
    hit->ray_dir_y = ray_dir_y;
    return (hit);
}

static void	render_column(t_game *game, int x)
{
    double		ray_dir_x;
    double		ray_dir_y;
    t_ray_hit	*hit;
    int			draw_start;
    int			draw_end;

    get_ray_direction(game, x, &ray_dir_x, &ray_dir_y);
    hit = cast_ray(game, ray_dir_x, ray_dir_y);
    if (!hit)
        return ;
    get_draw_bounds(hit, &draw_start, &draw_end);
    fill_background(game, x, draw_start, draw_end);
    draw_pixel_column(game, hit, x, draw_start, draw_end);
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