/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_sprites_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:54:54 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:54:54 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_duperror_msg(int mode, t_game *game)
{
	if (mode == 1 && game->locations.floor.red != -1)
		ft_error_msg("Duplicate identifier in the file.", game);
	if (mode == 2 && game->locations.ceiling.red != -1)
		ft_error_msg("Duplicate identifier in the file.", game);
}

int	find_map_utils(t_game *game, char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			break ;
		else if (ft_check_line(str + i) == 1)
			ft_error_msg("Found invalid character in the file.", game);
		i++;
	}
	if (str[i] == '\0')
		ft_error_msg("No map found in the file.", game);
	while (str[i] != '\n')
		i--;
	return (i);
}
