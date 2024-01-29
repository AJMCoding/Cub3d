#include "cub3d.h"

int	check_for_off_map(t_game *game, int i, int j)
{
	int	k;

	k = 0;
	while (game->map.full[i][k] != '\0')
	{
		if (k == j)
			return (0);
		k++;
	}
	return (1);
}

int	check_for_beyond_map(t_game *game, int i)
{
	int	k;

	k = 0;
	while (game->map.full[k] != NULL)
	{
		if (k == i)
			return (0);
		k++;
	}
	return (1);
}

int	find_color(t_game *game, int i, int j)
{
	int	color;

	i += (int)game->pl.pos.x - 5;
	j += (int)game->pl.pos.y - 5;
	if (i < 0 || j < 0)
		return (0x0000FF00);
	if (check_for_beyond_map(game, i) == 1)
		return (0x0000FF00);
	if (check_for_off_map(game, i, j) == 1)
		return (0x0000FF00);
	if (game->map.full[i][j] == '1')
		color = 0x00FF0000;
	else if (game->map.full[i][j] == '0' || game->map.full[i][j] == 'N'
		|| game->map.full[i][j] == 'S' || game->map.full[i][j] == 'E'
		|| game->map.full[i][j] == 'W')
		color = 0x00000000;
	else
		color = 0x0000FF00;
	return (color);
}

void	put_color(t_game *game, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 20)
	{
		y = 0;
		while (y < 20)
		{
			my_mlx_pixel_put(&game->img, j * 20 + x, i * 20 + y, color);
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			color = find_color(game, i, j);
			put_color(game, i, j, color);
			j++;
		}
		i++;
	}
	draw_character_line_of_sight(game);
}
