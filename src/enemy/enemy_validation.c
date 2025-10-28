/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	is_valid_enemy_position(t_game *game, int x, int y)
{
	int		i;
	char	tile;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	tile = game->map[y][x];
	if (tile == '1' || tile == 'S' || tile == 'E' || tile == 'C')
		return (0);
	if (x == game->player_x && y == game->player_y)
		return (0);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive && !game->enemies[i].is_dying)
		{
			if (game->enemies[i].x == x && game->enemies[i].y == y)
				return (0);
		}
		i++;
	}
	return (1);
}
