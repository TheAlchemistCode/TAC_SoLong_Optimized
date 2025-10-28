/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:18:33 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>

static void	check_row_length(t_game *game, int y)
{
	int	row_len;

	row_len = 0;
	while (game->map[y][row_len] && game->map[y][row_len] != '\n'
		&& game->map[y][row_len] != '\r')
		row_len++;
	if (row_len != game->map_width)
	{
		printf("Error: Map is not rectangular! Row %d", y);
		printf(" has length %d, expected %d\n", row_len, game->map_width);
		printf("Row content: '%s'\n", game->map[y]);
		exit(1);
	}
}

static void	verify_rectangular_shape(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		check_row_length(game, y);
		y++;
	}
}

static void	check_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' && game->map[0][i] != 'S')
		{
			printf("Error: Map is not enclosed by walls (top row)!\n");
			exit(1);
		}
		if (game->map[game->map_height - 1][i] != '1')
		{
			printf("Error: Map is not enclosed by walls (bottom row)!\n");
			exit(1);
		}
		i++;
	}
}

static void	check_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' && game->map[i][0] != 'S')
		{
			printf("Error: Map is not enclosed by walls (left side)!\n");
			exit(1);
		}
		if (game->map[i][game->map_width - 1] != '1')
		{
			printf("Error: Map is not enclosed by walls (right side)!\n");
			exit(1);
		}
		i++;
	}
}

void	check_map_structure(t_game *game)
{
	verify_rectangular_shape(game);
	check_horizontal_walls(game);
	check_vertical_walls(game);
}
