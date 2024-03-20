/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:20:03 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:20:03 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_data2 *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + ((y) * (data->bits_per_pixel / 8)
			+ (x * 64) * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_floor_ceiling(t_game *game, t_data2 img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(&img, x, y, game->images.floor);
			else
				my_mlx_pixel_put(&img, x, y, game->images.ceiling);
			y++;
		}
		x++;
	}
}
