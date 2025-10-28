/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:22:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:23:01 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_next_map_exists(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static void	setup_new_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"So Long - Next Level");
	if (!game->win)
	{
		printf("Error: Failed to create window for new level\n");
		exit(1);
	}
}

static void	setup_new_level(t_game *game, char *map_path)
{
	parse_map(map_path, game);
	validate_map(game, map_path);
	if (game->map[game->player_y][game->player_x] != 'P')
		game->map[game->player_y][game->player_x] = 'P';
	setup_new_window(game);
	init_textures(game);
	init_enemies(game);
	printf("\n⏱️ Time limit: %d seconds\n", MAP_TIME_LIMIT);
}

static void	register_handlers(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 17, 1L << 17, close_wrapper, game);
}

void	init_next_level(t_game *game, char *map_path)
{
	setup_new_level(game, map_path);
	register_handlers(game);
	render_map(game);
	render_enemies(game);
	game->map_start_time_ms = get_time_ms();
	game->time_remaining = MAP_TIME_LIMIT;
	game->last_printed_time = MAP_TIME_LIMIT;
	printf("⏱️ Time remaining: %d seconds\n\n", MAP_TIME_LIMIT);
}
