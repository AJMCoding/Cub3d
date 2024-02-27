#include "cub3d_bonus.h"

void	save_sprite(t_game *game, int x, int y)
{
	t_sprite	*tmp;
	//printf("save_sprite\n");

	if (game->sprites == NULL)
	{
		game->sprites = malloc(sizeof(t_sprite));
		if (game->sprites == NULL)
			ft_error_msg("Malloc Error", game);
		game->sprites->x = x;
		game->sprites->y = y;
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
		tmp->next->next = NULL;
	}
}

void	draw_sprite(t_game *game, int x, int y)
{
	//find angle between player and sprite
	double angle = atan2(game->pl.pos.y - y, game->pl.pos.x - x);
	double distance = sqrt((game->pl.pos.x - x) * (game->pl.pos.x - x) + (game->pl.pos.y - y) * (game->pl.pos.y - y));
	double range = distance * cos(angle);
	
	//double player_left_angle;
	double true_angle =  angle - atan2(game->pl.dir.y, game->pl.dir.x);
	printf("true_angle: %f\n", true_angle);
	printf("distance: %f\n", range);

	//find distance between player and sprite
	
}

void	draw_sprites(t_game *game)
{
	t_sprite	*tmp;
	//int			i;

	tmp = game->sprites;
	while (tmp != NULL)
	{
		draw_sprite(game, tmp->x + 0.5, tmp->y + 0.5);
		tmp = tmp->next;
	}
}