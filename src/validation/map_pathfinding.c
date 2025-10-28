/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:19:40 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * game->map_height);
	if (!map_copy)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			printf("Error: Memory allocation failed\n");
			exit(1);
		}
		i++;
	}
	return (map_copy);
}

static void	perform_flood_fill(t_game *game, char **map_copy)
{
	t_flood_data	data;

	data.map = map_copy;
	data.width = game->map_width;
	data.height = game->map_height;
	flood_fill_map(&data, game->player_x, game->player_y);
}

static void	count_reachable(t_game *game, char **map_copy, int *c, int *e)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'C' && map_copy[i][j] == 'V')
				(*c)++;
			else if (game->map[i][j] == 'E' && map_copy[i][j] == 'V')
				*e = 1;
			j++;
		}
		i++;
	}
}

void	validate_path_connectivity(t_game *game)
{
	char	**map_copy;
	int		collectibles_reachable;
	int		exit_reachable;

	collectibles_reachable = 0;
	exit_reachable = 0;
	map_copy = create_map_copy(game);
	perform_flood_fill(game, map_copy);
	count_reachable(game, map_copy, &collectibles_reachable, &exit_reachable);
	free_map_copy(map_copy, game->map_height);
	verify_reachability(game, collectibles_reachable, exit_reachable);
}
