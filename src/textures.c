/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/07/20 19:11:41 by szmadeja         ###   ########.fr       */
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

int	init_texture(t_game *game, char *path, t_texture *tex)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: invalid texture path: %s\n", path);
		return (1);
	}
	close (fd);
	if (!path || path[0] == '\0')
	{
		printf("Error: Invalid texture path\n");
		return (1);
	}
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Could not load texture: %s\n", path);
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

int	load_texture_side(t_game *game, char *map_line, t_texture *tex)
{
	char	*path;
	int		ret;

	if (!map_line)
		return (1);
	path = extract_path(map_line);
	ret = init_texture(game, path, tex);
	free(path);
	return (ret);
}

int	load_textures(t_game *game)
{
	if (!game->raw_map)
	{
		printf("Error: raw_map is NULL\n");
		return (1);
	}
	if (load_texture_side(game, game->raw_map->no, &game->no))
		return (1);
	if (load_texture_side(game, game->raw_map->so, &game->so))
		return (1);
	if (load_texture_side(game, game->raw_map->we, &game->we))
		return (1);
	if (load_texture_side(game, game->raw_map->ea, &game->ea))
		return (1);
	return (0);
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (!tex->addr || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
