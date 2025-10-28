/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_patrol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	move_right(t_game *game, t_enemy *enemy, int distance, t_position *pos)
{
	int	step;

	step = 0;
	while (step < distance)
	{
		if (pos->x + 1 >= enemy->start_x + enemy->patrol_length
			|| !is_valid_enemy_position(game, pos->x + 1, pos->y))
		{
			enemy->direction = 3;
			break ;
		}
		(pos->x)++;
		step++;
	}
}

void	move_left(t_game *game, t_enemy *enemy, int distance, t_position *pos)
{
	int	step;

	step = 0;
	while (step < distance)
	{
		if (pos->x - 1 <= enemy->start_x - enemy->patrol_length
			|| !is_valid_enemy_position(game, pos->x - 1, pos->y))
		{
			enemy->direction = 1;
			break ;
		}
		(pos->x)--;
		step++;
	}
}

void	move_down(t_game *game, t_enemy *enemy, int distance, t_position *pos)
{
	int	step;

	step = 0;
	while (step < distance)
	{
		if (pos->y + 1 >= enemy->start_y + enemy->patrol_length
			|| !is_valid_enemy_position(game, pos->x, pos->y + 1))
		{
			enemy->direction = 0;
			break ;
		}
		(pos->y)++;
		step++;
	}
}

void	move_up(t_game *game, t_enemy *enemy, int distance, t_position *pos)
{
	int	step;

	step = 0;
	while (step < distance)
	{
		if (pos->y - 1 <= enemy->start_y - enemy->patrol_length
			|| !is_valid_enemy_position(game, pos->x, pos->y - 1))
		{
			enemy->direction = 2;
			break ;
		}
		(pos->y)--;
		step++;
	}
}
