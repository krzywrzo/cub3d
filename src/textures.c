/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:00:00 by szmadeja          #+#    #+#             */
/*   Updated: 2026/06/21 16:53:26 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*extract_path(char *line)
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

static void	init_texture(t_game *game, char *path, t_texture *tex)
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

void	load_textures(t_game *game)
{
    char	*path;

    if (!game->raw_map)
    {
        printf("Error: raw_map is NULL\n");
        return ;
    }
    if (game->raw_map->no)
    {
        path = extract_path(game->raw_map->no);
        init_texture(game, path, &game->no);
        free(path);
    }
    if (game->raw_map->so)
    {
        path = extract_path(game->raw_map->so);
        init_texture(game, path, &game->so);
        free(path);
    }
    if (game->raw_map->we)
    {
        path = extract_path(game->raw_map->we);
        init_texture(game, path, &game->we);
        free(path);
    }
    if (game->raw_map->ea)
    {
        path = extract_path(game->raw_map->ea);
        init_texture(game, path, &game->ea);
        free(path);
    }
}

int	get_texture_color(t_texture *tex, int x, int y)
{
    char	*dst;

    if (!tex->addr || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
        return (0);
    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}