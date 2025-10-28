/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:27 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:07:25 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	close_wrapper(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	return (close_game(game));
}

static void	handle_movement(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 87)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 115 || keycode == 83)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == 97 || keycode == 65)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 100 || keycode == 68)
		move_player(game, game->player_x + 1, game->player_y);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	else if (keycode == 32)
	{
		if (!game->player_is_attacking)
		{
			player_attack(game);
			render_map(game);
			render_enemies(game);
		}
	}
	else
		handle_movement(keycode, game);
	return (0);
}

int	key_press_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	return (handle_keypress(keycode, game));
}
