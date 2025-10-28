/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_components.c                                   :+:      :+:    :+:   */
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

static void	count_player(t_game *game, int *p_count)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				(*p_count)++;
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
}

static void	count_exits_collectibles(t_game *game, int *e_count, int *c_count)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'E')
				(*e_count)++;
			else if (game->map[y][x] == 'C')
				(*c_count)++;
			x++;
		}
		y++;
	}
}

static void	verify_counts(int p_count, int e_count, int c_count)
{
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		printf("Error: Map component count is wrong!\n");
		exit(1);
	}
}

void	check_map_components(t_game *game)
{
	int	p_count;
	int	e_count;
	int	c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	count_player(game, &p_count);
	count_exits_collectibles(game, &e_count, &c_count);
	verify_counts(p_count, e_count, c_count);
	game->collectibles = c_count;
}
