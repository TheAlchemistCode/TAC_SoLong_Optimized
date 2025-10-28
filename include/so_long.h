/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:22:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/18 19:23:01 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define ATTACK_COOLDOWN_MS 1000
# define ENEMY_ATTACK_COOLDOWN_MS 800
# define PLAYER_ATTACK_COOLDOWN_MS 300
# define ATTACK_ANIM_DURATION_MS 200
# define DEATH_ANIM_DURATION_MS 300
# define PLAYER_MAX_HEALTH 240
# define ENEMY_ATTACK_DAMAGE 20
# define PLAYER_ATTACK_DAMAGE 50
# define ATTACK_DIR_LEFT 0
# define ATTACK_DIR_RIGHT 1
# define PLAYER_ATTACK_ANIM_DURATION 200
# define IDLE_FRAME_0_DURATION 600
# define IDLE_FRAME_1_DURATION 500
# define ENEMY_MOVE_DELAY_MS 2000
# define ENEMY_MIN_TILES 2
# define ENEMY_MAX_TILES 3
# define MAP_TIME_LIMIT 15

/*Position structure*/
typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

/*Flood fill data structure*/
typedef struct s_flood_data
{
	char	**map;
	int		width;
	int		height;
}	t_flood_data;

/*Movement patterns for enemies*/
typedef enum e_movement_pattern
{
	PATROL_HORIZONTAL,
	PATROL_VERTICAL,
	PATROL_RANDOM
}	t_movement_pattern;

/*Enemy structure*/
typedef struct s_enemy
{
	int					x;
	int					y;
	int					health;
	int					alive;
	int					is_attacking;
	int					attack_frame_index;
	int					last_attack_time_ms;
	int					attack_anim_start_ms;
	void				*idle_img;
	void				*attack_frames[2];
	void				*dead_img;
	int					is_dying;
	int					death_start_ms;
	int					frame_w;
	int					frame_h;
/*Movement fields*/
	int					start_x;
	int					start_y;
	int					last_move_time;
	int					direction;
	int					patrol_length;
	t_movement_pattern	pattern;
}	t_enemy;

/*GAME STUFF*/
typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	int				map_width;
	int				map_height;
	int				collectibles;
	int				collected;
	int				moves;
	int				player_x;
	int				player_y;
	int				player_health;
	int				player_last_attack_ms;
	int				player_is_attacking;
	int				player_attack_direction;
	int				player_attack_start_ms;
	int				player_idle_frame;
	int				player_idle_frame_start_ms;
	int				player_last_action_ms;
	int				exit_x;
	int				exit_y;
	int				victory;
	int				current_map;
/*Graphics textures*/
	void			*wall_img;
	void			*floor_img;
	void			*stat_tile_img;
	void			*collectible_img;
	void			*exit_img;
	void			*player_img;
	void			*player_idle_img2;
	void			*player_attack_left_img;
	void			*player_attack_right_img;
/*Enemy system*/
	t_enemy			*enemies;
	int				enemy_count;
/*Timer system*/
	int				map_start_time_ms;
	int				time_remaining;
	int				last_printed_time;
/*Game state*/
	int				game_ended;
}	t_game;

/*Function prototypes*/
void	parse_map(char *filename, t_game *game);
void	validate_map(t_game *game, char *filename);
void	validate_path(t_game *game);

/*Map validation functions (validation/)*/
void	check_map_components(t_game *game);
void	check_map_structure(t_game *game);
void	validate_path_connectivity(t_game *game);
void	flood_fill_map(t_flood_data *data, int x, int y);
void	free_map_copy(char **map_copy, int height);
void	verify_reachability(t_game *game, int c_reach, int e_reach);

/*Graphics functions*/
void	init_graphics(t_game *game);
void	init_textures(t_game *game);
void	render_map(t_game *game);
void	render_ui_overlay(t_game *game);
int		move_player(t_game *game, int new_x, int new_y);
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
void	cleanup_level(t_game *game);
void	display_victory(t_game *game);
void	load_next_map(t_game *game);
int		check_next_map_exists(char *map_path);
void	init_next_level(t_game *game, char *map_path);
int		key_press_handler(int keycode, void *param);
int		close_wrapper(void *param);
void	*get_player_sprite(t_game *game);
void	update_player_animation(t_game *game);
int		game_loop(t_game *game);

/*Enemy functions*/
void	init_enemies(t_game *game);
void	update_enemies(t_game *game);
void	render_enemies(t_game *game);
void	enemy_attack_player(t_game *game, t_enemy *enemy);
void	free_enemies(t_game *game);
void	update_enemy_movement(t_game *game);
int		is_valid_enemy_position(t_game *game, int x, int y);
void	calculate_next_position(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	move_right(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	move_left(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	move_down(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	move_up(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	patrol_horizontal(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	patrol_vertical(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);
void	random_movement(t_game *game, t_enemy *enemy,
			int distance, t_position *pos);

/*Combat functions*/
int		is_adjacent(int x1, int y1, int x2, int y2);
void	player_attack(t_game *game);
void	check_enemy_attacks(t_game *game);
int		has_living_enemy_at(t_game *game, int x, int y);
void	update_attack_state(t_game *game, int dx);
void	process_player_hit(t_game *game, int enemy_idx);
void	process_enemy_attack(t_game *game, int enemy_idx);

/*Animation functions*/
void	update_enemy_animation(t_enemy *enemy, int current_time);
void	load_enemy_textures(t_game *game, t_enemy *enemy);

/*Utility functions*/
int		get_time_ms(void);
int		update_map_timer(t_game *game);

#endif
