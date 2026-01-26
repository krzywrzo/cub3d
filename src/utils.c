/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:30:06 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/01/26 17:19:05 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_strlcmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_struct(t_map *map)
{
	int	i;
	int	j;

	if (map->no)
		printf("%s\n", map->no);
	if (map->ea)
		printf("%s\n", map->ea);
	if (map->so)
		printf("%s\n", map->so);
	if (map->we)
		printf("%s\n", map->we);
	printf("MAP\n");
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			printf("%c", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int handle_error()
{
	return (1);
}
