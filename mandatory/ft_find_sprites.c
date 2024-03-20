/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:21:48 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:21:49 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_image_type(char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (2);
	if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		return (3);
	if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		return (4);
	return (0);
}

int	add_image(t_game *game, char *str, int i)
{
	int	mode;
	int	j;

	j = 0;
	mode = find_image_type(str, i);
	i += 2;
	while (str[i] == ' ')
		i++;
	while (str[i + j] != '\0' && str[i + j] != '\n'
		&& str[i + j] != ' ' && str[i + j] != '\t')
		j++;
	if (mode == 1 && game->locations.north == NULL)
		game->locations.north = ft_strldup_save(str + i, j, game);
	else if (mode == 2 && game->locations.south == NULL)
		game->locations.south = ft_strldup_save(str + i, j, game);
	else if (mode == 3 && game->locations.west == NULL)
		game->locations.west = ft_strldup_save(str + i, j, game);
	else if (mode == 4 && game->locations.east == NULL)
		game->locations.east = ft_strldup_save(str + i, j, game);
	else
		ft_error_msg("Duplicate identifier in the file.", game);
	return (i + j);
}

void	check_all_found_error(t_game *game)
{
	if (game->locations.north == NULL)
		ft_error_msg("The north image is missing.", game);
	if (game->locations.south == NULL)
		ft_error_msg("The south image is missing.", game);
	if (game->locations.west == NULL)
		ft_error_msg("The west image is missing.", game);
	if (game->locations.east == NULL)
		ft_error_msg("The east image is missing.", game);
	if (game->locations.ceiling.red == -1 || game->locations.ceiling.green == -1
		|| game->locations.ceiling.blue == -1)
		ft_error_msg("The ceiling colour is missing.", game);
	if (game->locations.floor.red == -1 || game->locations.floor.green == -1
		|| game->locations.floor.blue == -1)
		ft_error_msg("The floor colour is missing.", game);
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
		&& game->locations.floor.blue != -1)
		return (1);
	return (0);
}

int	find_sprites(t_game *game, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || i == 0)
		{
			if (str[i] == '\n' && str[i + 1] != '\n' && str[i + 1] != '\0')
				i++;
			if (compare_to_identifier(str, i) == 1)
				add_image(game, str, i);
			else if (compare_to_identifier(str, i) == 2)
				add_colour(game, str, i);
			else if (compare_to_identifier(str, i) == 3)
				ft_error_msg("Image or color is not valid!", game);
		}
		i++;
		if (check_all_found(game) == 1)
			break ;
	}
	check_all_found_error(game);
	while (str[i] != '\n')
		i++;
	return (i);
}
