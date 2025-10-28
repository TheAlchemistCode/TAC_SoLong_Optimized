/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:04:55 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:07:49 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include <stdio.h>

static void	render_ui_text(t_game *game, char **ui_strings)
{
	int	health_color;
	int	timer_color;

	mlx_string_put(game->mlx, game->win, 10, 20, 0xFF8800, ui_strings[0]);
	if (game->player_health > 100)
		health_color = 0xFF8800;
	else if (game->player_health > 60)
		health_color = 0xFF8800;
	else
		health_color = 0xFF0000;
	mlx_string_put(game->mlx, game->win, 10, 40, health_color, ui_strings[1]);
	if (game->collectibles > 0)
		mlx_string_put(game->mlx, game->win, 10, 60, 0xFF8800, ui_strings[2]);
	else
		mlx_string_put(game->mlx, game->win, 10, 60, 0xFF8800,
			"Find the exit!");
	if (game->time_remaining > 5)
		timer_color = 0xFF8800;
	else if (game->time_remaining > 0)
		timer_color = 0xFF6600;
	else
		timer_color = 0xFF0000;
	mlx_string_put(game->mlx, game->win, 10, 80, timer_color, ui_strings[3]);
}

void	render_ui_overlay(t_game *game)
{
	char	moves_str[50];
	char	health_str[50];
	char	fish_str[50];
	char	timer_str[50];
	char	*ui_strings[4];

	sprintf(moves_str, "Moves: %d", game->moves);
	sprintf(health_str, "Health: %d/%d", game->player_health,
		PLAYER_MAX_HEALTH);
	sprintf(fish_str, "Fish: %d", game->collectibles);
	sprintf(timer_str, "Time: %d", game->time_remaining);
	ui_strings[0] = moves_str;
	ui_strings[1] = health_str;
	ui_strings[2] = fish_str;
	ui_strings[3] = timer_str;
	render_ui_text(game, ui_strings);
}

static void	render_map_tiles(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'S')
		mlx_put_image_to_window(game->mlx, game->win, game->stat_tile_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->floor_img,
			x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_map_objects(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, get_player_sprite(game),
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->collectible_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit_img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_map_tiles(game, x, y);
			render_map_objects(game, x, y);
			x++;
		}
		y++;
	}
	render_ui_overlay(game);
}
