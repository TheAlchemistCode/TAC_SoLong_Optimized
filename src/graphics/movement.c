/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:41 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:30:38 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <unistd.h>

static int	handle_exit_tile(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		game->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->moves++;
		render_map(game);
		render_enemies(game);
		usleep(1000000);
		load_next_map(game);
		return (1);
	}
	else if (game->map[new_y][new_x] == 'E' && game->collectibles > 0)
		return (0);
	return (-1);
}

static int	check_enemy_collision(t_game *game, int new_x, int new_y, int *i)
{
	if (game->map[new_y][new_x] == 'B')
	{
		*i = 0;
		while (*i < game->enemy_count)
		{
			if (game->enemies[*i].x == new_x
				&& game->enemies[*i].y == new_y
				&& game->enemies[*i].alive)
				return (1);
			(*i)++;
		}
		game->map[new_y][new_x] = '0';
		return (0);
	}
	return (-1);
}

static void	finalize_movement(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	game->player_last_action_ms = get_time_ms();
	game->player_idle_frame = 0;
	game->player_idle_frame_start_ms = game->player_last_action_ms;
	update_enemies(game);
	render_map(game);
	render_enemies(game);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	int	i;
	int	exit_result;

	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1' || game->map[new_y][new_x] == 'S')
		return (0);
	if (has_living_enemy_at(game, new_x, new_y))
		return (0);
	i = 0;
	if (check_enemy_collision(game, new_x, new_y, &i) == 1)
		return (0);
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	exit_result = handle_exit_tile(game, new_x, new_y);
	if (exit_result == 1)
		return (1);
	if (exit_result == 0)
		return (0);
	finalize_movement(game, new_x, new_y);
	return (1);
}
