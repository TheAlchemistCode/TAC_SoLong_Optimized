/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:00 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:18:33 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static int	is_valid_position(t_flood_data *data, int x, int y)
{
	if (x < 0 || x >= data->width)
		return (0);
	if (y < 0 || y >= data->height)
		return (0);
	return (1);
}

static int	is_walkable(t_flood_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (0);
	if (data->map[y][x] == 'S')
		return (0);
	if (data->map[y][x] == 'V')
		return (0);
	return (1);
}

static void	mark_visited(t_flood_data *data, int x, int y)
{
	data->map[y][x] = 'V';
}

static void	flood_fill_directions(t_flood_data *data, int x, int y)
{
	flood_fill_map(data, x + 1, y);
	flood_fill_map(data, x - 1, y);
	flood_fill_map(data, x, y + 1);
	flood_fill_map(data, x, y - 1);
}

void	flood_fill_map(t_flood_data *data, int x, int y)
{
	if (!is_valid_position(data, x, y))
		return ;
	if (!is_walkable(data, x, y))
		return ;
	mark_visited(data, x, y);
	flood_fill_directions(data, x, y);
}
