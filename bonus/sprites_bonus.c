#include "cub3d_bonus.h"
#include <unistd.h>

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

double	convert_angle(double angle, double range)
{
	angle = angle * 180.0/3.14159265358979323846 - 180.0;
	//angle = angle + ;
	(void)range;
	double	starting_point = ((float)WIN_WIDTH / 2) - (int)(angle * ((double)WIN_WIDTH / 66));
	printf("starting_point: %f\n", starting_point);
	return (starting_point);
}

void	draw_sprite_2(t_game *game, double distance, double starting_point)
{
	//printf("draw_sprite_2\n");
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

void	draw_sprite(t_game *game, double x, double y)
{
	double angle;
	double distance;
	double range;
	double relative_angle;
	double true_angle;
	double starting_point;

	//printf("pl.dir.x:%f pl.dir.y:%f\n", game->pl.dir.x, game->pl.dir.y);
	angle = atan2(game->pl.pos.y - y, game->pl.pos.x - x);
	if (angle < 0)
		angle = 360/(180.0/3.14159265358979323846) + angle;
	distance = sqrt((game->pl.pos.x - x) * (game->pl.pos.x - x) + (game->pl.pos.y - y) * (game->pl.pos.y - y));
	range = distance * cos(angle);
	relative_angle = atan2(game->pl.pos.y - (game->pl.pos.y - pow(game->pl.dir.y, 2)), game->pl.pos.x - (game->pl.pos.x - pow(game->pl.dir.x, 2)));
 	if (game->pl.dir.x < 0)
	{
		if (game->pl.dir.y < 0)
			relative_angle = 0.5 * 360/(180.0/3.14159265358979323846) + relative_angle;
		else
			relative_angle = 0.5 * 360/(180.0/3.14159265358979323846) - relative_angle;
	}
	else 
	{
		if (game->pl.dir.y < 0)
			relative_angle = 1 * 360/(180.0/3.14159265358979323846) - relative_angle;
		else
			relative_angle = 0 * 360/(180.0/3.14159265358979323846) + relative_angle;
	
	}
	printf("player.x:%f player.y:%f\n", game->pl.dir.x, game->pl.dir.y);
	printf("relative_angle: %f\n", relative_angle);
	relative_angle = atan2(game->pl.dir.y, game->pl.dir.x);
	if (relative_angle < 0)
		relative_angle = 360/(180.0/3.14159265358979323846) + relative_angle;
	printf("relative_angle: %f\n", relative_angle);
	//relative_angle = atan2(pow(game->pl.dir.y,2), pow(game->pl.dir.x,2));
	//printf("dir.y2:%f dir.x2:%f\n", pow(game->pl.dir.y,2), pow(game->pl.dir.x, 2));
	//relative_angle = atan2(game->pl.pos.y - (game->pl.pos.y - pow(game->pl.dir.y, 2)), game->pl.pos.x - (game->pl.pos.x - pow(game->pl.dir.x, 2)));
	//printf("game->pl.dir.x:%f game->pl.dir.y:%f\n", game->pl.dir.x, game->pl.dir.y);
	true_angle =  angle - relative_angle;
	//printf("true_angle: %f\n", true_angle);
	//printf("relative_angle: %f\n", relative_angle);
	if (true_angle < 0)
		true_angle = 360/(180.0/3.14159265358979323846) + true_angle;
	starting_point = convert_angle(true_angle, range);
	//printf("distance: %f\n", distance);
	//printf("range: %f\n", range);
	//printf("true_angle: %f\n", true_angle);

	draw_sprite_2(game, distance, starting_point);
	(void)range;
}

int	compare_range(t_sprite *tmp, t_sprite *tmp2, t_game *game)
{
	double	distance;
	double	distance2;
	double	angle;
	double	angle2;
	double	range;
	double	range2;

	distance = sqrt((game->pl.pos.x - tmp->x) * (game->pl.pos.x - tmp->x) + (game->pl.pos.y - tmp->y) * (game->pl.pos.y - tmp->y));
	distance2 = sqrt((game->pl.pos.x - tmp2->x) * (game->pl.pos.x - tmp2->x) + (game->pl.pos.y - tmp2->y) * (game->pl.pos.y - tmp2->y));
	angle = atan2(game->pl.pos.y - tmp->y, game->pl.pos.x - tmp->x);
	angle2 = atan2(game->pl.pos.y - tmp2->y, game->pl.pos.x - tmp2->y);
	range = distance * cos(angle);
	range2 = distance2 * cos(angle2);
	if (range > range2)
		return (1);
	return (0);
}

void	draw_sprites_2(t_game *game)
{
	t_sprite	*tmp;
	t_sprite	*tmp2;

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
	draw_sprite(game, tmp2->x + 0.5, tmp2->y + 0.5);
	tmp2->printed = 1;
}

int	list_size(t_sprite *sprites)
{
	t_sprite	*tmp;
	int			i;

	i = 0;
	tmp = sprites;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	draw_sprites(t_game *game)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	i = 0;

	i = list_size(game->sprites);
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