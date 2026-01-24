/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/01/24 19:42:22 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define WIDTH 1280
# define HEIGHT 720

/*	STRUCTS	*/
typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*celling;
}	t_map;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
}		t_cub;

/*	FUNCTIONS	*/
int handle_error();

//	parsing.c
int		map_parse(char *map_path);
char	space_to_zero (char s);
void	handle_line(t_map *map, char *line);
void	handle_file(int fd);

# endif
