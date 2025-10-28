/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_new.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:13:11 by clyon             #+#    #+#             */
/*   Updated: 2025/10/20 15:18:33 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdio.h>

void	validate_map(t_game *game, char *filename)
{
	check_map_components(game);
	check_map_structure(game);
	validate_path_connectivity(game);
	printf("Map validation successful! Loaded: %s\n", filename);
}

void	validate_path(t_game *game)
{
	validate_path_connectivity(game);
}
