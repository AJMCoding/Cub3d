/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sprites2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:21:56 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:21:57 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	find_number_length(char *str, int i, t_game *game, int num)
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
	if (str[i] == ',' && num == 2)
	{
		i++;
		length++;
	}
	else if (num == 2 || (num == 1 && (str[i] == '\0' || str[i] != '\n' )))
		ft_error_msg("A colour is not valid.", game);
	while ((str[i] == ' ') && num == 2)
	{
		length++;
		i++;
	}
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
	i = ft_duperror_msg(mode, game, i);
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 1)
		{
			if (ft_atoi_image(str, i) != 256)
				num = add_colour2(mode, ft_atoi_image(str, i), num, game);
			else
				ft_error_msg("A colour is not valid.", game);
			if (num == 3)
				i += find_number_length(str, i, game, 1);
			else
				i += find_number_length(str, i, game, 2);
		}
		else
			break ;
	}
	return (i);
}
