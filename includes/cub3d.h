/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/04/08 12:41:30 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "parsing.h"

# define WIDTH 1280
# define HEIGHT 720

// keyhooks detection
#if LINUX == 1
	# define KEY_ESC 65307
	# define KEY_W 119
	# define KEY_A 97
#else
	# define KEY_ESC 53
	# define KEY_W 13
	# define KEY_A 0
#endif

/*	STRUCTURES	*/
typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
}		t_cub;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;	// needed for MAC vs Linux (i will delete this later)
}		t_img;


/*	FUNCTIONS	*/

//	win_creation.c
int	close_app(void *param);
int	mlx_create_window(t_cub *mlx);
int	my_mlx_init(t_map *map, t_map_info *map_info);
void	my_pixel_put(t_img *img, int x, int y, int color);
# endif