/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:43:50 by kwrzosek          #+#    #+#             */
/*   Updated: 2026/01/24 18:57:30 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_error()
{
	printf("error");
	exit(1);
	return (1);
}

int main (int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("[DEBUG]: argv[1]: %s\n", argv[1]);
	if (map_parse(argv[1]) == 1)
	{
		return(handle_error());	//	TODO
	}
}
