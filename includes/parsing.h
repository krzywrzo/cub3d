/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:56:09 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/20 12:33:23 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
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
	char	*ea;
	char	*we;
	char	*f;
	char	*c;
	char	*raw_map;
	int		height;
	int		width;
	char	**grid;
	int		player_x;
	int		player_y;
	char	**map_copy;
	char	*direction;
}	t_map;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_tex;

typedef struct s_fc
{
	char	*f;
	char	*c;
}	t_fc;

/*	FUNCTIONS	*/
// flood_fill.c
int		check_player_count(char **grid);
int		check_map_validity(t_map *map);
char	*strjoin_with_newline(char *s1, char *s2);
int		flood_fill(char **grid, int x, int y, t_map *map);
int		get_player_pos(t_map *map);

// parsing.c
t_map	*parsing(int argc, char **argv);
int		parse_file_loop(int fd, t_map *map);

// utils_01.c
int		tex_checker(char *filename);
int		free_fc(t_fc *fc, int flag);
int		fc_checker(char *filename);
int		is_garbage_values(int fd);
int		free_tex(t_tex *tex, int flag);

// utils_02.c
int		is_empty_line(char *line);
int		all_elements_found(t_map *map);
int		assign_element(char **target, char *data);
int		parse_texture_or_color(char *line, t_map *map);
int		is_valid_map_line(char *line);

// utils_03.c
int		extract_map_line(char *line, t_map *map);
int		is_dups(int fd);		// too many lines
int		ext_checker(char *filename);
int		get_map_size(char **map, int flag);

// utils_04.c
int		get_map_height(char **map);
void	free_partial_copy(char **map_cp, int current_index);
char	**copy_map(char **map, int height);
void	get_size(char **grid, t_map *map);
void	free_split(char **split);

// utils_05.c
int		ft_strlcmp(const char *s1, const char *s2, size_t n);
int		split_size(char **arr);
int		handle_error(void);
void	copy_with_newline(char *new_str, char *s1, char *s2);

// utils_06.c
int		validate_parsed_map(t_map *map);
int		process_line(char *line, t_map *map);
int		check_texture(t_tex *tex, char *line);
int		check_line_garbage(char *line);

// utils_07.c
int		loop_fc(int fd, t_fc *fc);
int		check_fc_line(t_fc *fc, char *line);
void	free_map_strings(t_map *map);
void	clean_struct(t_map *map);
void	*abort_parsing(t_map *map, int fd, int do_drain);

#endif
