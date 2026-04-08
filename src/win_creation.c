/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:27:41 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/04/08 12:41:33 by kwrzosek         ###   ########.fr       */
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

}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pxl / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_init(t_map *map, t_map_info *map_info)
{
	t_cub 	cub;
	t_img	img;

	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (1);
	cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "cwel");
	if (!cub.win)
		return (1);
	img.img_ptr = mlx_new_image(cub.win, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pxl, &img.line_len, &img.endian);

	// mlx_hook(cub.win, 17, 0, close_app, &cub);
	// mlx_create_window(cub.mlx);
	mlx_put_image_to_window(cub.mlx, cub.win, img.img_ptr, 0, 0);
	mlx_loop(cub.mlx);
	return (0);
}
