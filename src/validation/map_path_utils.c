/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:19:40 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

void	verify_reachability(t_game *game, int c_reach, int e_reach)
{
	if (c_reach != game->collectibles)
	{
		printf("Error: Not all collectibles are reachable ");
		printf("from player start position\n");
		exit(1);
	}
	if (!e_reach)
	{
		printf("Error: Exit is not reachable ");
		printf("from player start position\n");
		exit(1);
	}
	printf("Path validation: All %d collectibles ", game->collectibles);
	printf("and exit are reachable!\n");
}
