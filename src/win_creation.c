/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:27:41 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/06/21 16:33:38 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return ;
    dst = img->addr + (y * img->line_len + x * (img->bits_per_pxl / 8));
    *(unsigned int *)dst = color;
}

static void	player_dir(t_player *player, t_map_info *map)
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

static t_player	*init_player(t_map_info *map)
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

static void	destroy_textures(t_game *game)
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

int	close_app(void *param)
{
    t_game	*game;

    game = (t_game *)param;
    destroy_textures(game);
    if (game->frame.img_ptr)
        mlx_destroy_image(game->mlx, game->frame.img_ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->player);
    free(game->mlx);
    free(game);
    exit(0);
    return (0);
}

static int	init_mlx_frame(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (1);
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
    if (!game->win)
        return (1);
    game->frame.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->frame.img_ptr)
        return (1);
    game->frame.addr = mlx_get_data_addr(game->frame.img_ptr,
            &game->frame.bits_per_pxl, &game->frame.line_len,
            &game->frame.endian);
    return (0);
}

static void	setup_hooks(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, (int (*)())key_press, game);
    mlx_hook(game->win, 3, 1L << 1, (int (*)())key_release, game);
    mlx_hook(game->win, 17, 0, (int (*)())close_app, game);
    mlx_loop_hook(game->mlx, (int (*)())game_loop, game);
}

int	my_mlx_init(t_map_info *map_info, t_map *raw_map)
{
    t_game	*game;

    game = ft_calloc(1, sizeof(t_game));
    if (!game)
        return (1);
    if (!raw_map)
    {
        printf("Error: raw_map is NULL\n");
        free(game);
        return (1);
    }
    game->map = map_info;
    game->raw_map = raw_map;
    game->player = init_player(map_info);
    if (!game->player)
        return (1);
    if (init_mlx_frame(game) == 1)
        return (1);
    load_textures(game);
    setup_hooks(game);
    mlx_loop(game->mlx);
    return (0);
}
