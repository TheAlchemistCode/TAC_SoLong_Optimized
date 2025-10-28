/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 16:34:19 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	render_single_enemy(t_game *game, t_enemy *enemy)
{
	void	*img;
	int		x;
	int		y;

	if (!enemy->alive)
		return ;
	x = enemy->x * TILE_SIZE;
	y = enemy->y * TILE_SIZE;
	if (enemy->is_dying)
		img = enemy->dead_img;
	else if (enemy->is_attacking)
		img = enemy->attack_frames[enemy->attack_frame_index];
	else
		img = enemy->idle_img;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img, x, y);
}

void	render_enemies(t_game *game)
{
	int	i;

	if (!game->enemies)
		return ;
	i = 0;
	while (i < game->enemy_count)
		render_single_enemy(game, &game->enemies[i++]);
}
