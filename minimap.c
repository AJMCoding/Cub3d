#include "cub3d.h"

void	draw_minimap2(t_game *game)
{
	int i;
	int j;
	int x;
	int y;
	int color;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (game->map.full[i] != NULL)
	{
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == '1')
				color = 0x00FF0000;
			else if (game->map.full[i][j] == '0' || game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S' || game->map.full[i][j] == 'E' || game->map.full[i][j] == 'W')
				color = 0x00000000;
			else if (game->map.full[i][j] == '2')
				color = 0x0000FF00;
			else
				color = 0x00FFFFFF;
			if (j == (int)game->pl.pos.y && i == (int)game->pl.pos.x)
				color = 0x000000FF;
			while (x < 10)
			{
				while (y < 10)
				{
					my_mlx_pixel_put(&game->img, j * 10 + x, i * 10 + y, color);
					y++;
				}
				y = 0;
				x++;
			}
			x = 0;
			j++;
		}
		j = 0;
		i++;
	}
}


void	draw_minimap(t_game *game)
{
	draw_minimap2(game);
}