/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:20:43 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/05/15 14:09:04 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	tex_checker(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error with opening file\n");
		return (-1);
	}
	if (is_dups(fd) == -1)
	{
		close(fd);
		perror("Duplicated textures\n");
		return (-1);
	}
	if (is_garbage_values(fd) == -1)
	{
		close(fd);
		perror("Error: Found garbage values in textures path\n");
		return (-1);
	}
	close(fd);
	return (0);
}

int	free_fc(t_fc *fc, int flag)
{
	free(fc->f);
	free(fc->c);
	free(fc);
	if (flag == 0)
		return (0);
	return (-1);
}

int	fc_checker(char *filename)
{
	t_fc	*fc;
	int		fd;

	fc = ft_calloc(1, sizeof(t_fc));
	if (!fc)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error with opening file\n");
		free(fc);
		return (-1);
	}
	if (loop_fc(fd, fc) == 1)
	{
		close(fd);
		return (free_fc(fc, 1));
	}
	close(fd);
	return (free_fc(fc, 0));
}

// int	fc_checker(char *filename)
// {
// 	int		fd;
// 	t_fc	*fc;
// 	char	*line;

// 	fc = malloc(sizeof(t_fc));
// 	if (!fc)
// 		return (-1);
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error with opening file\n");
// 		return (-1);
// 	}
// 	while (ft_strlen(line = get_next_line(fd)) > 0)
// 	{
// 		if (ft_strlcmp(line, "F", 1) == 0)
// 			if (fc->f != NULL)
// 				return (free_fc(fc, 1));
// 		else if (ft_strlcmp(line, "C", 1) == 0)
// 			if (fc->c != NULL)
// 				return (free_fc(fc, 1));
// 	}
// 	close(fd);
// 	return (free_fc(fc, 0));
// }

int	is_garbage_values(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strlen(line) > 0)
	{
		if (check_line_garbage(line) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}

// int	is_garbage_values(int fd)
// {
// 	char	*line;
// 	char	**splitted_tex;

// 	while (ft_strlen(line = get_next_line(fd)) > 0)
// 	{
// 		splitted_tex = ft_split(line, ' ');
// 		if (split_size(splitted_tex, ' ') != 2)
// 		{
// 			free_split(splitted_tex);
// 			return (-1);
// 		}
// 	}
// 	free_split(splitted_tex);
// 	return (0);
// }

int	free_tex(t_tex *tex, int flag)
{
	if (!tex)
		return (-1);
	free(tex->no);
	free(tex->ea);
	free(tex->so);
	free(tex->we);
	free(tex);
	if (flag == 0)
		return (0);
	return (-1);
}
