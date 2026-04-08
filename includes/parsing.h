/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:56:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/04/08 16:57:50 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

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
	char	*one_line_map;
	char	**map;
}	t_map;


// main map structur, with all of crucial data needed, 
// if u need to add something, add this in struct_filler function
typedef struct s_map_info
{
	int	player_x;
	int	player_y;
	int	map_width;
	int	map_height;
	char	direction;
	char	**map_copy;
}	t_map_info;



/*	FUNCTIONS	*/


//	parsing.c
t_map	*map_parse(char *map_path);
void	handle_line(t_map *map, char *line);
t_map	*handle_file(int fd);
t_map	*parser(char **argv);

//	cleaners.c
void	free_split(char **str);
void	free_map(t_map *map);

//	utils.c
int 	ft_strlcmp(const char *s1, const char *s2, size_t n);
void	print_struct(t_map *map);
int		handle_error();

//	flood_fill.c
int flood_fill(t_map_info *map_info, int x, int y);
int	is_map_correct(t_map *map);

//	flood_fill_utils.c
void	map_info_print(t_map_info *map_info);
t_map_info *struct_filler(t_map *map);
void get_pos(char **map, t_map_info *map_info);
void	get_size(char **map, t_map_info *map_info);

# endif
