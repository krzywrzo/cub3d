/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 16:30:55 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include "parsing.h"
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

#if LINUX == 1
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#else
#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#endif

typedef struct s_img
{
    void	*img_ptr;
    char	*addr;
    int		bits_per_pxl;
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_player
{
    double	pos_x;
    double	pos_y;
    double	view_dir_x;
    double	view_dir_y;
    double	plane_x;
    double	plane_y;
}	t_player;

typedef struct s_texture
{
    void	*img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
    int		width;
    int		height;
}	t_texture;

typedef struct s_ray_hit
{
    double	distance;
    int		side;
    double	ray_dir_x;
    double	ray_dir_y;
}	t_ray_hit;

typedef struct s_draw_col
{
    int		x;
    int		draw_start;
    int		draw_end;
    int		tex_x;
    t_texture	*tex;
}	t_draw_col;

typedef struct s_keys
{
    int	w;
    int	a;
    int	s;
    int	d;
    int	left;
    int	right;
    int	esc;
}	t_keys;

typedef struct s_game
{
    void		*mlx;
    void		*win;
    t_img		frame;
    t_player	*player;
    t_map_info	*map;
    t_map		*raw_map;
    t_texture	no;
    t_texture	so;
    t_texture	we;
    t_texture	ea;
    t_keys		keys;
}	t_game;

int		close_app(void *param);
int		my_mlx_init(t_map_info *map_info, t_map *raw_map);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		game_loop(void *param);
void	load_textures(t_game *game);
void	render_scene(t_game *game);
int		get_texture_color(t_texture *tex, int x, int y);
void	my_pixel_put(t_img *img, int x, int y, int color);

#endif