/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:11 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:07:08 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdlib.h>
#include <unistd.h>

static void	destroy_all_images(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->stat_tile_img)
		mlx_destroy_image(game->mlx, game->stat_tile_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->player_attack_left_img)
		mlx_destroy_image(game->mlx, game->player_attack_left_img);
	if (game->player_attack_right_img)
		mlx_destroy_image(game->mlx, game->player_attack_right_img);
	if (game->player_idle_img2)
		mlx_destroy_image(game->mlx, game->player_idle_img2);
}

int	close_game(t_game *game)
{
	destroy_all_images(game);
	free_enemies(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	exit(0);
	return (0);
}

static void	free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	cleanup_level(t_game *game)
{
	free_map(game);
	free_enemies(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	destroy_all_images(game);
	game->wall_img = NULL;
	game->floor_img = NULL;
	game->stat_tile_img = NULL;
	game->player_img = NULL;
	game->collectible_img = NULL;
	game->exit_img = NULL;
}
