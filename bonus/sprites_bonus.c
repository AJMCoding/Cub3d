#include "cub3d_bonus.h"
#include <unistd.h>

void	save_sprite(t_game *game, int x, int y)
{
	t_sprite	*tmp;

	if (game->sprites == NULL)
	{
		game->sprites = malloc(sizeof(t_sprite));
		if (game->sprites == NULL)
			ft_error_msg("Malloc Error", game);
		game->sprites->x = x;
		game->sprites->y = y;
		game->sprites->printed = 0;
		game->sprites->next = NULL;
	}
	else
	{
		tmp = game->sprites;
		while (tmp->next != NULL)
		{
			if (tmp->x == x && tmp->y == y)
				return ;
			tmp = tmp->next;
		}
		if (tmp->x == x && tmp->y == y)
			return ;
		tmp->next = malloc(sizeof(t_sprite));
		tmp->next->x = x;
		tmp->next->y = y;
		tmp->next->printed = 0;
		tmp->next->next = NULL;
	}
}

void	draw_sprite(t_game *game, double distance, double starting_point)
{
	double		height;
	double		width;
	double		x;
	double		y;
	int			i;
	int			j;
	int			color;

	height = (WIN_HEIGHT / distance * 0.66) * 1.2;
	width = (WIN_HEIGHT / distance * 0.66) * 1.2;
	x = starting_point - (width / 2);
	y = ((float)WIN_HEIGHT / 2) - (height / 2);
	i = 0;
	while (i < width)
	{
		j = 0;
		if (x + i < 0 || x + i >= WIN_WIDTH)
		{
			i++;
			continue ;
		}
		if (game->distances[(int)x + i] < distance)
		{
			i++;
			continue ;
		}
		while (j < height)
		{
			if (x + i >= 0 && x + i < WIN_WIDTH && y + j >= 0 && y + j < WIN_HEIGHT)
			{
				color = my_mlx_pixel_get(&game->images.sprite_data, (j / height) * game->images.sprite.height, (i / width) * game->images.sprite.width);
				if (color != 0)
					my_mlx_pixel_put(&game->img, x + i, y + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites_2(t_game *game)
{
	t_sprite	*tmp;
	t_sprite	*tmp2;
	t_sprite_calc	calc;

	tmp = game->sprites;
	tmp2 = game->sprites;
	while (tmp2->printed == 1)
		tmp2 = tmp2->next;
	while (tmp)
	{
		if (tmp->printed == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (compare_range(tmp, tmp2, game) == 1)
			tmp2 = tmp;
		tmp = tmp->next;
	}
	calc = calc_sprite(game, tmp2->x + 0.5, tmp2->y + 0.5);
	draw_sprite(game, calc.range, calc.starting_point);
	tmp2->printed = 1;
}

void	draw_sprites(t_game *game)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	i = 0;

	i = list_size_sprites(game->sprites);
	j = 0;
	while (j < i)
	{
		draw_sprites_2(game);
		j++;
	}
	tmp = game->sprites;
	while (tmp)
	{
		tmp->printed = 0;
		tmp = tmp->next;
	}
}