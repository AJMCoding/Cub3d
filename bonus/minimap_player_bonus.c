/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:18:46 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:18:47 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_player_circle(t_game *game, double x, double y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		while (j < 10)
		{
			if (sqrt(pow(i - 5, 2) + pow(j - 5, 2)) < 5)
				my_mlx_pixel_put(&game->img, y - 5 + j, x - 5 + i, 0x000000FF);
			j++;
		}
		j = 0;
		i++;
	}
}

void	put_line_of_sight(t_game *game, double x, double y)
{
	double	camera;
	double	dir_x;
	double	dir_y;	

	camera = 2 * 0 / (double)WIN_WIDTH - 1;
	dir_x = game->pl.dir.x + game->pl.plane.x * camera;
	dir_y = game->pl.dir.y + game->pl.plane.y * camera;
	while (x > 0 && y > 0 && x < 200 && y < 200)
	{
		x += dir_x / 5;
		y += dir_y / 5;
		if (x < 0 || y < 0)
			return ;
		my_mlx_pixel_put(&game->img, y, x, 0x000000FF);
	}
}

void	put_line_of_sight2(t_game *game, double x, double y)
{
	double	camera;
	double	dir_x;
	double	dir_y;	

	camera = (2 * WIN_WIDTH - 1) / (double)WIN_WIDTH - 1;
	dir_x = game->pl.dir.x + game->pl.plane.x * camera;
	dir_y = game->pl.dir.y + game->pl.plane.y * camera;
	while (x > 0 && y > 0 && x < 200 && y < 200)
	{
		x += dir_x / 5;
		y += dir_y / 5;
		if (x < 0 || y < 0)
			return ;
		my_mlx_pixel_put(&game->img, y, x, 0x000000FF);
	}
}

void	put_outline(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 200)
	{
		my_mlx_pixel_put(&game->img, 0, i, 0x000000FF);
		my_mlx_pixel_put(&game->img, 199, i, 0x000000FF);
		my_mlx_pixel_put(&game->img, 200, i, 0x000000FF);
		my_mlx_pixel_put(&game->img, i, 0, 0x000000FF);
		my_mlx_pixel_put(&game->img, i, 199, 0x000000FF);
		my_mlx_pixel_put(&game->img, i, 200, 0x000000FF);
		i++;
	}
}

void	draw_character_line_of_sight(t_game *game)
{
	double	x;
	double	y;

	x = ((game->pl.pos.x - (int)game->pl.pos.x) * 10) + 105;
	y = ((game->pl.pos.y - (int)game->pl.pos.y) * 10) + 105;
	put_player_circle(game, x, y);
	put_line_of_sight(game, x, y);
	put_line_of_sight2(game, x, y);
	put_outline(game);
}
