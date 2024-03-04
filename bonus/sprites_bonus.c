#include "cub3d_bonus.h"

void	put_sprite_pixel(t_sprite_drawing sd, t_game *game, t_sprite *sprite)
{
	sd.color = find_sprite_color(sprite,
			(sd.j / sd.height) * game->images.sprite.height,
			(sd.i / sd.width) * game->images.sprite.width, game);
	if (sd.color != 0)
		my_mlx_pixel_put(&game->img, sd.x + sd.i,
			sd.y + sd.j, sd.color);
}

void	draw_sprite_2(t_sprite_drawing sd, t_game *game, double distance,
					t_sprite *sprite)
{
	while (sd.i < sd.width)
	{
		sd.j = 0;
		if (sd.x + sd.i < 0 || sd.x + sd.i >= WIN_WIDTH)
		{
			sd.i++;
			continue ;
		}
		if (game->distances[(int)sd.x + sd.i -1] < distance)
		{
			sd.i++;
			continue ;
		}
		while (sd.j < sd.height)
		{
			if (sd.x + sd.i >= 0 && sd.x + sd.i < WIN_WIDTH
				&& sd.y + sd.j >= 0 && sd.y + sd.j < WIN_HEIGHT)
				put_sprite_pixel(sd, game, sprite);
			sd.j++;
		}
		sd.i++;
	}
}

void	draw_sprite(t_game *game, double distance,
					double starting_point, t_sprite *sprite)
{
	t_sprite_drawing	sd;

	sd.height = (WIN_HEIGHT / distance * 0.66) * 1.2;
	sd.width = (WIN_HEIGHT / distance * 0.66) * 1.2;
	sd.x = starting_point - (sd.width / 2);
	sd.y = ((float)WIN_HEIGHT / 2) - (sd.height / 2);
	sd.i = 0;
	if (distance < 0.2)
		return ;
	draw_sprite_2(sd, game, distance, sprite);
}

void	draw_sprites_2(t_game *game)
{
	t_sprite		*tmp;
	t_sprite		*tmp2;
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
	draw_sprite(game, calc.range, calc.starting_point, tmp2);
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
