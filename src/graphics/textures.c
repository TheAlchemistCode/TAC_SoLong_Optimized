/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:15:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:13:49 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <unistd.h>
#include <stdlib.h>

static void	load_floor_wall(t_game *game, int *width, int *height)
{
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"assets/bgtile_walkable.xpm", width, height);
	if (!game->floor_img)
	{
		write(2, "Error: Failed to load floor texture\n", 37);
		exit(1);
	}
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"assets/bgtile_bush.xpm", width, height);
	if (!game->wall_img)
	{
		write(2, "Error: Failed to load wall texture\n", 36);
		exit(1);
	}
}

static void	load_player_idle(t_game *game, int *width, int *height)
{
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player/goodsprite_idle.xpm", width, height);
	if (!game->player_img)
	{
		write(2, "Error: Failed to load player texture\n", 38);
		exit(1);
	}
	game->player_idle_img2 = mlx_xpm_file_to_image(game->mlx,
			"assets/player/goodsprite_idle_2.xpm", width, height);
	if (!game->player_idle_img2)
	{
		write(2, "Error: Failed to load player idle 2 texture\n", 45);
		exit(1);
	}
}

static void	load_player_attack(t_game *game, int *width, int *height)
{
	game->player_attack_left_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player/goodsprite_attack_L.xpm", width, height);
	if (!game->player_attack_left_img)
	{
		write(2, "Error: Failed to load player attack left texture\n", 50);
		exit(1);
	}
	game->player_attack_right_img = mlx_xpm_file_to_image(game->mlx,
			"assets/player/goodsprite_attack_R.xpm", width, height);
	if (!game->player_attack_right_img)
	{
		write(2, "Error: Failed to load player attack right texture\n", 51);
		exit(1);
	}
}

static void	load_items(t_game *game, int *width, int *height)
{
	game->stat_tile_img = mlx_xpm_file_to_image(game->mlx,
			"assets/black_tile.xpm", width, height);
	if (!game->stat_tile_img)
	{
		write(2, "Error: Failed to load stat tile texture\n", 41);
		exit(1);
	}
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"assets/fish.xpm", width, height);
	if (!game->collectible_img)
	{
		write(2, "Error: Failed to load collectible texture\n", 42);
		exit(1);
	}
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"assets/exit.xpm", width, height);
	if (!game->exit_img)
	{
		write(2, "Error: Failed to load exit texture\n", 36);
		exit(1);
	}
}

void	init_textures(t_game *game)
{
	int	width;
	int	height;

	load_floor_wall(game, &width, &height);
	load_items(game, &width, &height);
	load_player_idle(game, &width, &height);
	load_player_attack(game, &width, &height);
}
