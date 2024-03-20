/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:20:23 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:20:24 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strldup_save(char *s, size_t len, t_game *game)
{
	char	*str;

	str = ft_strldup(s, len);
	if (str == NULL)
		ft_error_msg("Malloc error.", game);
	return (str);
}

void	movements(t_game *game)
{
	if (game->input.turn_left == 1 && game->input.turn_right == 0)
		rotate_camera(game, 0, 0.03);
	if (game->input.turn_left == 0 && game->input.turn_right == 1)
		rotate_camera(game, 1, 0.03);
	if (game->input.front == 1 && game->input.back == 0)
		change_player_pos(game, 1);
	if (game->input.front == 0 && game->input.back == 1)
		change_player_pos(game, -1);
	if (game->input.left == 1 && game->input.right == 0)
		change_player_pos_side(game, -1);
	if (game->input.left == 0 && game->input.right == 1)
		change_player_pos_side(game, 1);
}

int	check_all_found(t_game *game)
{
	if (game->locations.north != NULL
		&& game->locations.south != NULL
		&& game->locations.west != NULL
		&& game->locations.east != NULL
		&& game->locations.ceiling.red != -1
		&& game->locations.ceiling.green != -1
		&& game->locations.ceiling.blue != -1
		&& game->locations.floor.red != -1
		&& game->locations.floor.green != -1
		&& game->locations.floor.blue != -1
		&& game->locations.sprite != NULL
		&& game->locations.door != NULL
		&& game->locations.a_sprite1 != NULL
		&& game->locations.a_sprite2 != NULL)
		return (1);
	return (0);
}
