/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 19:21:08 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "parsing.h"
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_dda
{
	int		map_xy[2];
	double		delta_dist[2];
	double		side_dist[4];
	int		step[2];
	int		side;
}		t_dda;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}		t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	view_dir_x;
	double	view_dir_y;
	double	plane_x;
	double	plane_y;
}		t_player;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}		t_texture;

typedef struct s_ray_hit
{
	double	distance;
	int		side;
	double	ray_dir_x;
	double	ray_dir_y;
}		t_ray_hit;

typedef struct s_draw_col
{
	int			x;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	t_texture	*tex;
}		t_draw_col;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}		t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_player	*player;
	t_map		*map;
	t_map		*raw_map;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_keys		keys;
}		t_game;

int		close_app(void *param);
int		my_mlx_init(t_map *map_info, t_map *raw_map);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		game_loop(void *param);
void	load_textures(t_game *game);
void	render_scene(t_game *game);
int		get_texture_color(t_texture *tex, int x, int y);
void	my_pixel_put(t_img *img, int x, int y, int color);

/* raycasting_dda.c */
void	dda_init(t_game *game, t_dda *dda);
void	dda_step_x(t_game *game, double ray_x, t_dda *dda);
void	dda_step_y(t_game *game, double ray_y, t_dda *dda);
int		is_wall_hit(t_game *game, int map_x, int map_y);
void	dda_loop(t_game *game, t_dda *dda);

/* raycasting_texture.c */
t_texture	*pick_texture(t_game *game, int side, double ray_x,
			double ray_y);
void	calc_wall_x(t_game *game, t_ray_hit *hit, double *wall_x);
int		calc_tex_x(t_texture *tex, double wall_x, t_ray_hit *hit);
void	set_delta_distances(double ray_x, double ray_y, t_dda *dda);
void	set_hit_distance(t_ray_hit *hit, t_dda *dda);

/* raycasting_draw.c */
void	fill_background(t_game *game, int x, int draw_start, int draw_end);
void	get_draw_bounds(t_ray_hit *hit, int *draw_start, int *draw_end);
void	init_draw_col(t_game *game, t_ray_hit *hit, t_draw_col *col);
void	draw_pixels(t_game *game, t_draw_col *col);
void	draw_pixel_column(t_game *game, t_ray_hit *hit, t_draw_col *col);

/* raycasting_ray.c */
void	get_ray_direction(t_game *game, int x, double *ray_dir_x,
			double *ray_dir_y);
t_ray_hit	*cast_ray(t_game *game, double ray_dir_x, double ray_dir_y);
void	render_column(t_game *game, int x);

/* hooks_movement.c */
int		is_wall(t_map *map, double x, double y);
void	check_and_move_x(t_game *game, double move_x);
void	check_and_move_y(t_game *game, double move_y);
void	rotate_player(t_player *p, double rot);
void	handle_movement(t_game *game);

/* textures.c */
char	*extract_path(char *line);
void	init_texture(t_game *game, char *path, t_texture *tex);
void	load_texture_side(t_game *game, char *map_line, t_texture *tex);

/* player_init.c */
void	player_dir(t_player *player, t_map *map);
t_player	*init_player(t_map *map);
void	destroy_textures(t_game *game);

#endif