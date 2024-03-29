/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:14:43 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:14:47 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_direction2(t_game *game, char direction)
{
	if (direction == 'W')
	{
		game->pl.dir.x = 0.0000;
		game->pl.dir.y = -1.0000;
		game->pl.plane.x = -0.66;
		game->pl.plane.y = 0.0;
	}
	if (direction == 'E')
	{
		game->pl.dir.x = 0.0000;
		game->pl.dir.y = 1.0000;
		game->pl.plane.x = 0.66;
		game->pl.plane.y = 0.0;
	}
}

void	update_direction(t_game *game, char direction, int i, int j)
{
	game->pl.pos.x = i + 0.5;
	game->pl.pos.y = j + 0.5;
	if (direction == 'N')
	{
		game->pl.dir.x = -1.0000;
		game->pl.dir.y = 0.0000;
		game->pl.plane.x = 0.0;
		game->pl.plane.y = 0.66;
	}
	if (direction == 'S')
	{
		game->pl.dir.x = 1.0000;
		game->pl.dir.y = 0.0000;
		game->pl.plane.x = 0.0;
		game->pl.plane.y = -0.66;
	}
	update_direction2(game, direction);
}

void	save_door(t_game *game, int i, int j)
{
	t_door	*door;
	t_door	*tmp;

	door = malloc(sizeof(t_door));
	if (door == NULL)
		ft_error_msg("Malloc error.", game);
	door->x = i;
	door->y = j;
	door->open = 1;
	door->next = NULL;
	if (game->doors == NULL)
	{
		game->doors = door;
	}
	else
	{
		tmp = game->doors;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = door;
	}
}

void	check_parameters(t_game *game, int i, int j)
{
	int	found;

	i = 0;
	found = 0;
	while (game->map.full[i] != NULL)
	{
		j = 0;
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == 'W' || game->map.full[i][j] == 'E'
				|| game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S')
			{
				update_direction(game, game->map.full[i][j], i, j);
				found++;
			}
			if (game->map.full[i][j] == 'D')
				save_door(game, i, j);
			if (char_part_of_map(game->map.full[i][j]) == 0)
				ft_error_msg("The map contains invalid characters.", game);
			j++;
		}
		i++;
	}
	if (found != 1)
		ft_error_msg("The map has the wrong amount of players.", game);
}

void	ft_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_parameters(game, i, j);
	check_surrounded(game);
}
