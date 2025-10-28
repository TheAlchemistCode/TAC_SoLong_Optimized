/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:35 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:24:14 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	display_victory(t_game *game)
{
	printf("Level completed in %d moves!\n", game->moves);
}

void	load_next_map(t_game *game)
{
	char	map_path[256];

	game->current_map++;
	sprintf(map_path, "maps/map%d.ber", game->current_map);
	if (!check_next_map_exists(map_path))
	{
		game->game_ended = 1;
		printf("\n🏆 ALL LEVELS COMPLETED! 🏆\n");
		printf("Total moves: %d\n", game->moves);
		usleep(3000000);
		close_game(game);
		return ;
	}
	display_victory(game);
	usleep(2000000);
	cleanup_level(game);
	game->collectibles = 0;
	game->player_health = PLAYER_MAX_HEALTH;
	game->player_last_attack_ms = 0;
	game->enemy_count = 0;
	game->moves = 0;
	init_next_level(game, map_path);
}
