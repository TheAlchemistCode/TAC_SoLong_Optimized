/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
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
#include <time.h>

static int	count_enemies(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'B')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	setup_enemy_stats(t_enemy *enemy, int x, int y, int index)
{
	enemy->x = x;
	enemy->y = y;
	enemy->health = 100;
	enemy->alive = 1;
	enemy->is_attacking = 0;
	enemy->attack_frame_index = 0;
	enemy->last_attack_time_ms = 0;
	enemy->attack_anim_start_ms = 0;
	enemy->is_dying = 0;
	enemy->death_start_ms = 0;
	enemy->start_x = x;
	enemy->start_y = y;
	enemy->last_move_time = get_time_ms();
	enemy->direction = rand() % 4;
	enemy->patrol_length = 5;
	if (index % 2 == 0)
		enemy->pattern = PATROL_HORIZONTAL;
	else
		enemy->pattern = PATROL_VERTICAL;
}

static void	init_single_enemy(t_game *game, int x, int y, int index)
{
	setup_enemy_stats(&game->enemies[index], x, y, index);
	load_enemy_textures(game, &game->enemies[index]);
	printf("Enemy initialized at position (%d, %d)\n", x, y);
}

static void	scan_map_for_enemies(t_game *game)
{
	int	y;
	int	x;
	int	index;

	index = 0;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			if (game->map[y][x] == 'B')
				init_single_enemy(game, x, y, index++);
	}
	printf("Total enemies initialized: %d\n", game->enemy_count);
}

void	init_enemies(t_game *game)
{
	game->enemy_count = count_enemies(game);
	if (game->enemy_count == 0)
	{
		game->enemies = NULL;
		printf("No enemies found in map\n");
		return ;
	}
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
	{
		printf("Error: Failed to allocate memory for enemies\n");
		exit(1);
	}
	scan_map_for_enemies(game);
}
