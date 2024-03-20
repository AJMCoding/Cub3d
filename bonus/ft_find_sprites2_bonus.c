/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sprites2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:17:31 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:17:34 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	compare_to_identifier(char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'S' && str[i + 1] == 'P' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'D' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'A' && str[i + 1] == '1' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'A' && str[i + 1] == '2' && str[i + 2] == ' ')
		return (1);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		return (2);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		return (2);
	else if (str[i] == '\n' || str[i] == '\0')
		return (0);
	else
		return (3);
	return (0);
}

int	find_number_length(char *str, int i)
{
	int	length;

	length = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 1)
			length++;
		else
			break ;
		i++;
	}
	length++;
	return (length);
}

int	find_color_type(char *str, int i)
{
	if (str[i] == 'F' && str[i + 1] == ' ')
		return (1);
	if (str[i] == 'C' && str[i + 1] == ' ')
		return (2);
	return (0);
}

int	add_colour2(int mode, int value, int pos, t_game *game)
{
	if (pos > 2)
		ft_error_msg("A colour is not valid.", game);
	if (mode == 1)
	{
		if (pos == 0)
			game->locations.floor.red = value;
		if (pos == 1)
			game->locations.floor.green = value;
		if (pos == 2)
			game->locations.floor.blue = value;
	}
	if (mode == 2)
	{
		if (pos == 0)
			game->locations.ceiling.red = value;
		if (pos == 1)
			game->locations.ceiling.green = value;
		if (pos == 2)
			game->locations.ceiling.blue = value;
	}
	return (pos + 1);
}

int	add_colour(t_game *game, char *str, int i)
{
	int	mode;
	int	num;

	num = 0;
	mode = find_color_type(str, i);
	if (mode == 1 && game->locations.floor.red != -1)
		ft_error_msg("Duplicate identifier in the file.", game);
	if (mode == 2 && game->locations.ceiling.red != -1)
		ft_error_msg("Duplicate identifier in the file.", game);
	i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 1)
		{
			if (ft_atoi_image(str, i) != 256)
				num = add_colour2(mode, ft_atoi_image(str, i), num, game);
			else
				ft_error_msg("A colour is not valid.", game);
			i += find_number_length(str, i);
		}
		else
			break ;
	}
	return (i);
}
