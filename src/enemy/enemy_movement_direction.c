/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_direction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdlib.h>

void	patrol_horizontal(t_game *game, t_enemy *enemy,
	int distance, t_position *pos)
{
	if (enemy->direction == 1 || enemy->direction == 0)
		move_right(game, enemy, distance, pos);
	else
		move_left(game, enemy, distance, pos);
}

void	patrol_vertical(t_game *game, t_enemy *enemy,
	int distance, t_position *pos)
{
	if (enemy->direction == 2 || enemy->direction == 1)
		move_down(game, enemy, distance, pos);
	else
		move_up(game, enemy, distance, pos);
}

static void	set_random_direction(int *dx, int *dy, int direction)
{
	*dx = 0;
	*dy = 0;
	if (direction == 0)
		*dy = -1;
	else if (direction == 1)
		*dx = 1;
	else if (direction == 2)
		*dy = 1;
	else
		*dx = -1;
}

void	random_movement(t_game *game, t_enemy *enemy,
	int distance, t_position *pos)
{
	int	step;
	int	dx;
	int	dy;

	set_random_direction(&dx, &dy, enemy->direction);
	step = 0;
	while (step < distance)
	{
		if (!is_valid_enemy_position(game, pos->x + dx, pos->y + dy))
		{
			enemy->direction = rand() % 4;
			break ;
		}
		pos->x += dx;
		pos->y += dy;
		step++;
	}
}
