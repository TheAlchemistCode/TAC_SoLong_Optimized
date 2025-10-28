/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 17:36:45 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void	process_enemy_state(t_enemy *enemy, int current_time)
{
	if (enemy->is_dying)
	{
		if (current_time - enemy->death_start_ms >= DEATH_ANIM_DURATION_MS)
		{
			enemy->alive = 0;
			printf("Enemy death animation complete\n");
		}
	}
	else
		update_enemy_animation(enemy, current_time);
}

void	update_enemies(t_game *game)
{
	int	current_time;
	int	i;

	if (!game->enemies)
		return ;
	current_time = get_time_ms();
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive)
			process_enemy_state(&game->enemies[i], current_time);
		i++;
	}
	update_enemy_movement(game);
	check_enemy_attacks(game);
}

static void	process_enemy_movement(t_game *game, t_enemy *enemy, int index)
{
	int			current_time;
	t_position	pos;

	current_time = get_time_ms();
	if (current_time - enemy->last_move_time >= ENEMY_MOVE_DELAY_MS)
	{
		pos.x = enemy->x;
		pos.y = enemy->y;
		calculate_next_position(game, enemy, 1, &pos);
		if (is_valid_enemy_position(game, pos.x, pos.y))
		{
			enemy->x = pos.x;
			enemy->y = pos.y;
			printf("Enemy %d moved to (%d, %d)\n", index, pos.x, pos.y);
		}
		enemy->last_move_time = current_time;
	}
}

void	update_enemy_movement(t_game *game)
{
	int	i;

	if (!game->enemies)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].alive && !game->enemies[i].is_dying
			&& !game->enemies[i].is_attacking)
			process_enemy_movement(game, &game->enemies[i], i);
		i++;
	}
}

void	calculate_next_position(t_game *game, t_enemy *enemy,
	int distance, t_position *pos)
{
	pos->x = enemy->x;
	pos->y = enemy->y;
	if (enemy->pattern == PATROL_HORIZONTAL)
		patrol_horizontal(game, enemy, distance, pos);
	else if (enemy->pattern == PATROL_VERTICAL)
		patrol_vertical(game, enemy, distance, pos);
	else
		random_movement(game, enemy, distance, pos);
}
