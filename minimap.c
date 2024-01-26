#include "cub3d.h"
#include <linux/limits.h>

int	check_for_off_map(t_game *game, int i, int j)
{
	int k;

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
	int k;

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
	int color;
	i += game->pl.pos.x - 5;
	j += game->pl.pos.y - 5;
	if (check_for_beyond_map(game, i) == 1)
		return (0x0000FF00);
	if (i < 0 || j < 0 || game->map.full[i] == NULL || game->map.full[i][j] == '\0')
		return (0x0000FF00);
	if (check_for_off_map(game, i, j) == 1)
		return (0x0000FF00);
	if (game->map.full[i][j] == '1')
		color = 0x00FF0000;
	else if (game->map.full[i][j] == '0' || game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S' || game->map.full[i][j] == 'E' || game->map.full[i][j] == 'W')
		color = 0x00000000;
	else
		color = 0x0000FF00;
	return (color);
}

void	put_color(t_game *game, int i, int j, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < 20)
	{
		while (y < 20)
		{
			my_mlx_pixel_put(&game->img, j * 20 + x, i * 20 + y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void draw_minimap4(t_game *game)
{
	int i;
	int j;
	int color;

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
}

void	put_player_circle(t_game *game, double x, double y)
{
	int i;
	int j;

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
	double cameraX = 2 * 0 / (double)WIN_WIDTH - 1;
	double dir_x = game->pl.dir.x + game->pl.plane.x * cameraX;
	double dir_y = game->pl.dir.y + game->pl.plane.y * cameraX;
	//printf("dir_x: %f dir_y: %f\n", dir_x, dir_y);
	while (x > 0 && y > 0 && x < 200 && y < 200)
	{
		printf("x: %f y: %f\n", x, y);
		x += dir_x / 5;
		y += dir_y / 5;
		if (x < 0 || y < 0)
			return ;
		my_mlx_pixel_put(&game->img, y, x, 0x000000FF);
	}
}

void	put_line_of_sight2(t_game *game, double x, double y)
{
	double cameraX = 2 * 959 / (double)WIN_WIDTH - 1;
	double dir_x = game->pl.dir.x + game->pl.plane.x * cameraX;
	double dir_y = game->pl.dir.y + game->pl.plane.y * cameraX;
	//printf("dir_x: %f dir_y: %f\n", dir_x, dir_y);
	while (x > 0 && y > 0 && x < 200 && y < 200)
	{
		printf("x: %f y: %f\n", x, y);
		x += dir_x / 5;
		y += dir_y / 5;
		if (x < 0 || y < 0)
			return ;
		my_mlx_pixel_put(&game->img, y, x, 0x000000FF);
	}
}

void	draw_character_line_of_sight(t_game *game)
{
	double x;
	double y;

	x = ((game->pl.pos.x - (int)game->pl.pos.x) * 10) + 105;
	y = ((game->pl.pos.y - (int)game->pl.pos.y) * 10) + 105;
	put_player_circle(game, x, y);
	put_line_of_sight(game, x, y);
	put_line_of_sight2(game, x, y);
}


void	draw_minimap(t_game *game)
{
	draw_minimap4(game);
	draw_character_line_of_sight(game);
}