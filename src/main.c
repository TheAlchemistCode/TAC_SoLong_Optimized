/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:29:42 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 16:29:42 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static void	init_game_state(t_game *game)
{
	game->moves = 0;
	game->victory = 0;
	game->player_health = PLAYER_MAX_HEALTH;
	game->player_last_attack_ms = 0;
	game->player_idle_frame = 0;
	game->player_idle_frame_start_ms = get_time_ms();
	game->player_last_action_ms = get_time_ms();
	game->map_start_time_ms = get_time_ms();
	game->time_remaining = MAP_TIME_LIMIT;
	game->last_printed_time = MAP_TIME_LIMIT;
	game->game_ended = 0;
}

static void	set_initial_level(char *map_file, t_game *game)
{
	int	map_number;

	if (sscanf(map_file, "maps/map%d.ber", &map_number) == 1)
		game->current_map = map_number;
	else if (strstr(map_file, "map1.ber"))
		game->current_map = 1;
	else if (strstr(map_file, "map2.ber"))
		game->current_map = 2;
	else
		game->current_map = 1;
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 1L << 17, close_wrapper, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	srand(time(NULL));
	if (argc != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1);
	}
	parse_map(argv[1], &game);
	validate_map(&game, argv[1]);
	init_game_state(&game);
	set_initial_level(argv[1], &game);
	init_graphics(&game);
	init_textures(&game);
	init_enemies(&game);
	render_map(&game);
	render_enemies(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
