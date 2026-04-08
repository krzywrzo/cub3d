/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:27:41 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/04/08 16:51:45 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_app(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	// mlx_destroy_display(cub->mlx);	// only on linux
	free(cub->mlx);
	exit(0);
	return (0);
}

int	mlx_create_window(t_cub *mlx)
{
	return 0;
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pxl / 8));
	*(unsigned int *)dst = color;
}
//	TODO: add struct with map info
void	player_dir(t_player *player, t_map_info *map)
{
	if (map->direction == 'N')
	{
		player->view_dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (map->direction == 'S')
	{
		player->view_dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (map->direction == 'E')
	{
		player->view_dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (map->direction == 'W')
	{
		player->view_dir_x = -1;
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
	player->plane_x = 0;
	player->plane_y = 0;
	player_dir(player, map);
	return(player);
}


void draw_background(t_img *img)
{
    int x;
    int y;
    int color;

    // Define some basic Hex colors (0xRRGGBB)
    int sky_blue = 0x87CEEB;
    int floor_green = 0x228B22;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // If we are in the top half of the screen, draw sky
            if (y < HEIGHT / 2)
                color = sky_blue;
            // Otherwise, we are in the bottom half, draw floor
            else
                color = floor_green;

            // Use our custom pixel put to write directly to memory
            my_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}


int	my_mlx_init(t_map_info *map_info)
{
	t_cub 	cub;
	t_img	img;
	t_player	*player;

	player = init_player(map_info);
	if (!player)
		return (1);
	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (1);
	cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "cwel");
	if (!cub.win)
		return (1);
	img.img_ptr = mlx_new_image(cub.win, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pxl, &img.line_len, &img.endian);

	mlx_hook(cub.win, 17, 0, close_app, &cub);
	// mlx_create_window(cub.mlx);
	// draw_background(&img);
	mlx_put_image_to_window(cub.mlx, cub.win, img.img_ptr, 0, 0);
	mlx_loop(cub.mlx);
	return (0);
}
