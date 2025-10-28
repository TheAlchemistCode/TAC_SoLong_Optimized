/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:48 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:26:18 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>

static void	*handle_attack_animation(t_game *game, unsigned long now)
{
	unsigned long	elapsed;
	void			*sprite;

	elapsed = now - game->player_attack_start_ms;
	if (elapsed < PLAYER_ATTACK_ANIM_DURATION)
	{
		if (game->player_attack_direction == ATTACK_DIR_LEFT)
			sprite = game->player_attack_left_img;
		else
			sprite = game->player_attack_right_img;
		return (sprite);
	}
	game->player_is_attacking = 0;
	game->player_last_action_ms = now;
	game->player_idle_frame = 0;
	game->player_idle_frame_start_ms = now;
	return (NULL);
}

static void	*get_idle_sprite(t_game *game, unsigned long now)
{
	unsigned long	elapsed;

	elapsed = now - game->player_idle_frame_start_ms;
	if (game->player_idle_frame == 0)
	{
		if (elapsed >= IDLE_FRAME_0_DURATION)
		{
			game->player_idle_frame = 1;
			game->player_idle_frame_start_ms = now;
		}
		if (game->player_idle_frame == 1)
			return (game->player_idle_img2);
		return (game->player_img);
	}
	if (elapsed >= IDLE_FRAME_1_DURATION)
	{
		game->player_idle_frame = 0;
		game->player_idle_frame_start_ms = now;
	}
	if (game->player_idle_frame == 0)
		return (game->player_img);
	return (game->player_idle_img2);
}

void	*get_player_sprite(t_game *game)
{
	int		now;
	void	*sprite;

	now = get_time_ms();
	if (game->player_is_attacking)
	{
		sprite = handle_attack_animation(game, now);
		if (sprite)
			return (sprite);
	}
	return (get_idle_sprite(game, now));
}

void	update_player_animation(t_game *game)
{
	int			now;
	static int	last_render = 0;

	now = get_time_ms();
	if (game->player_is_attacking)
	{
		if (now - game->player_attack_start_ms >= PLAYER_ATTACK_ANIM_DURATION)
		{
			game->player_is_attacking = 0;
			game->player_last_action_ms = now;
			game->player_idle_frame = 0;
			game->player_idle_frame_start_ms = now;
			render_map(game);
			render_enemies(game);
			last_render = now;
		}
	}
	else if (now - last_render > 50)
	{
		render_map(game);
		render_enemies(game);
		last_render = now;
	}
}

int	game_loop(t_game *game)
{
	update_player_animation(game);
	update_enemies(game);
	if (!update_map_timer(game))
	{
		printf("\n💀 GAME OVER! Time expired!\n");
		printf("Final score: %d moves\n", game->moves);
		close_game(game);
		exit(0);
	}
	return (0);
}
