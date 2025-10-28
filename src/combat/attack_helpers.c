/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 18:01:39 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>

void	update_attack_state(t_game *game, int dx)
{
	int	current_time;

	current_time = get_time_ms();
	game->player_is_attacking = 1;
	game->player_attack_start_ms = current_time;
	if (dx > 0)
		game->player_attack_direction = ATTACK_DIR_RIGHT;
	else if (dx < 0)
		game->player_attack_direction = ATTACK_DIR_LEFT;
	else
		game->player_attack_direction = ATTACK_DIR_RIGHT;
	game->player_last_attack_ms = current_time;
	game->player_last_action_ms = current_time;
	game->player_idle_frame = 0;
	game->player_idle_frame_start_ms = current_time;
}

void	process_player_hit(t_game *game, int enemy_idx)
{
	int	current_time;

	current_time = get_time_ms();
	game->enemies[enemy_idx].health -= PLAYER_ATTACK_DAMAGE;
	printf("💥 Enemy health: %d\n", game->enemies[enemy_idx].health);
	if (game->enemies[enemy_idx].health <= 0)
	{
		game->enemies[enemy_idx].is_dying = 1;
		game->enemies[enemy_idx].death_start_ms = current_time;
		if (game->map[game->enemies[enemy_idx].y]
			[game->enemies[enemy_idx].x] == 'B')
			game->map[game->enemies[enemy_idx].y]
			[game->enemies[enemy_idx].x] = '0';
		printf("💀 Enemy defeated! Playing death animation...\n");
	}
}

void	process_enemy_attack(t_game *game, int enemy_idx)
{
	int	current_time;

	current_time = get_time_ms();
	game->player_health -= ENEMY_ATTACK_DAMAGE;
	game->enemies[enemy_idx].last_attack_time_ms = current_time;
	game->enemies[enemy_idx].is_attacking = 1;
	game->enemies[enemy_idx].attack_anim_start_ms = current_time;
	game->enemies[enemy_idx].attack_frame_index = 0;
	printf("Enemy attacks! Player health: %d/%d\n",
		game->player_health, PLAYER_MAX_HEALTH);
	if (game->player_health <= 0)
	{
		printf("Game Over! You were defeated!\n");
		close_game(game);
	}
}
