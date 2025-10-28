/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 16:34:19 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>

int	is_adjacent(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	return ((dx + dy) == 1);
}

void	player_attack(t_game *game)
{
	int	current_time;
	int	i;
	int	dx;

	current_time = get_time_ms();
	if (game->player_is_attacking)
		return ;
	if (current_time - game->player_last_attack_ms < PLAYER_ATTACK_COOLDOWN_MS)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive
			&& is_adjacent(game->player_x, game->player_y,
				game->enemies[i].x, game->enemies[i].y))
		{
			dx = game->enemies[i].x - game->player_x;
			update_attack_state(game, dx);
			process_player_hit(game, i);
			return ;
		}
		i++;
	}
	printf("No enemy in range to attack!\n");
}

void	check_enemy_attacks(t_game *game)
{
	int	current_time;
	int	i;

	current_time = get_time_ms();
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive
			&& is_adjacent(game->player_x, game->player_y,
				game->enemies[i].x, game->enemies[i].y))
		{
			if (current_time - game->enemies[i].last_attack_time_ms
				>= ENEMY_ATTACK_COOLDOWN_MS)
				process_enemy_attack(game, i);
		}
		i++;
	}
}

int	has_living_enemy_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive && !game->enemies[i].is_dying
			&& game->enemies[i].x == x && game->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
