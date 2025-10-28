/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdlib.h>

void	free_enemies(t_game *game)
{
    int	i;

    if (!game->enemies)
        return ;
    i = 0;
    while (i < game->enemy_count)
    {
        if (game->enemies[i].idle_img)
            mlx_destroy_image(game->mlx, game->enemies[i].idle_img);
        if (game->enemies[i].attack_frames[0])
            mlx_destroy_image(game->mlx, game->enemies[i].attack_frames[0]);
        if (game->enemies[i].attack_frames[1])
            mlx_destroy_image(game->mlx, game->enemies[i].attack_frames[1]);
        if (game->enemies[i].dead_img)
            mlx_destroy_image(game->mlx, game->enemies[i].dead_img);
        i++;
    }
    free(game->enemies);
    game->enemies = NULL;
}
