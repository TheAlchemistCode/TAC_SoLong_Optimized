/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:30:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>

void	update_enemy_animation(t_enemy *enemy, int current_time)
{
	int	elapsed;

	if (!enemy->is_attacking)
		return ;
	elapsed = current_time - enemy->attack_anim_start_ms;
	if (elapsed >= ATTACK_ANIM_DURATION_MS)
	{
		enemy->is_attacking = 0;
		enemy->attack_frame_index = 0;
		return ;
	}
	if (elapsed < ATTACK_ANIM_DURATION_MS / 2)
		enemy->attack_frame_index = 0;
	else
		enemy->attack_frame_index = 1;
}

void	load_enemy_textures(t_game *game, t_enemy *enemy)
{
	int	width;
	int	height;

	enemy->idle_img = mlx_xpm_file_to_image(game->mlx,
			"assets/enemy/badsprite_idle.xpm", &width, &height);
	if (!enemy->idle_img)
		printf("Warning: Failed to load enemy idle sprite\n");
	enemy->attack_frames[0] = mlx_xpm_file_to_image(game->mlx,
			"assets/enemy/badsprite_attack.xpm", &width, &height);
	enemy->attack_frames[1] = mlx_xpm_file_to_image(game->mlx,
			"assets/enemy/badsprite_idle.xpm", &width, &height);
	if (!enemy->attack_frames[0] || !enemy->attack_frames[1])
		printf("Warning: Failed to load enemy attack animation frames\n");
	enemy->dead_img = mlx_xpm_file_to_image(game->mlx,
			"assets/enemy/badsprite_dead.xpm", &width, &height);
	if (!enemy->dead_img)
		printf("Warning: Failed to load enemy death sprite\n");
	enemy->frame_w = width;
	enemy->frame_h = height;
}
