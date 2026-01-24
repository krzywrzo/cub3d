/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/01/24 16:44:43 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main (int argc, char **argv)
{
	char	*map_path;

	if (argv != 2)
	{
		return (1);
	}
	ft_strlcpy(map_path, argv[1], ft_strlen(argv[1]));
	if (map_parse(map_path) == 1)
	{
		handle_error();	//	TODO
	}
}
