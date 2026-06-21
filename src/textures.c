/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 17:54:36 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*extract_path(char *line)
{
	char	*path;
	int		i;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}

void	init_texture(t_game *game, char *path, t_texture *tex)
{
	if (!path || path[0] == '\0')
	{
		printf("Error: Invalid texture path\n");
		return ;
	}
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Could not load texture: %s\n", path);
		return ;
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

void	load_texture_side(t_game *game, char *map_line, t_texture *tex)
{
	char	*path;

	if (!map_line)
		return ;
	path = extract_path(map_line);
	init_texture(game, path, tex);
	free(path);
}

void	load_textures(t_game *game)
{
	if (!game->raw_map)
	{
		printf("Error: raw_map is NULL\n");
		return ;
	}
	load_texture_side(game, game->raw_map->no, &game->no);
	load_texture_side(game, game->raw_map->so, &game->so);
	load_texture_side(game, game->raw_map->we, &game->we);
	load_texture_side(game, game->raw_map->ea, &game->ea);
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (!tex->addr || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
