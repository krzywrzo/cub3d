/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:58:21 by szmadeja          #+#    #+#             */
/*   Updated: 2026/01/24 18:33:34 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

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


/*	FUNCTIONS	*/
int handle_error();

//	parsing.c
int		map_parse(char *map_path);
char	space_to_zero (char s);
void	handle_line(t_map *map, char *line);
void	handle_file(int fd);
void	print_struct(t_map *map);

//	utils.c
int ft_strlcmp(const char *s1, const char *s2, size_t n);

# endif
