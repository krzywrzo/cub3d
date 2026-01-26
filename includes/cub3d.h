/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/01/26 17:18:56 by kwrzosek         ###   ########.fr       */
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
	char	*one_line_map;
	char	**map;
}	t_map;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
}		t_cub;

/*	FUNCTIONS	*/


//	parsing.c
t_map	*map_parse(char *map_path);
void	handle_line(t_map *map, char *line);
t_map	*handle_file(int fd);

//	cleaners.c
void	free_split(char **str);
void	free_map(t_map *map);

//	utils.c
int 	ft_strlcmp(const char *s1, const char *s2, size_t n);
void	print_struct(t_map *map);
int		handle_error();

# endif
