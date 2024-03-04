#include "cub3d_bonus.h"

void	new_sprite(t_game *game, int x, int y, int num)
{
	t_sprite	*tmp;

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
	if (tmp->next == NULL)
		ft_error_msg("Malloc Error", game);
	tmp->next->x = x;
	tmp->next->y = y;
	tmp->next->printed = 0;
	tmp->next->type = num;
	tmp->next->next = NULL;
}

void	save_sprite(t_game *game, int x, int y, int num)
{
	if (game->sprites == NULL)
	{
		game->sprites = malloc(sizeof(t_sprite));
		if (game->sprites == NULL)
			ft_error_msg("Malloc Error", game);
		game->sprites->x = x;
		game->sprites->y = y;
		game->sprites->printed = 0;
		game->sprites->type = num;
		game->sprites->next = NULL;
	}
	else
	{
		new_sprite(game, x, y, num);
	}
}

int	find_sprite_color(t_sprite *sprite, int x, int y, t_game *game)
{
	int		color;

	if (sprite->type == 2)
	{
		if (game->frame_num / 10 % 2 == 0)
			color = my_mlx_pixel_get(&game->images.a_sprite1_data, x, y);
		else
			color = my_mlx_pixel_get(&game->images.a_sprite2_data, x, y);
	}
	else
		color = my_mlx_pixel_get(&game->images.sprite_data, x, y);
	return (color);
}
