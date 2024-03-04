#include "cub3d_bonus.h"

double	convert_angle(double angle, double range)
{
	double	sp;

	angle = angle * 180.0 / 3.14159265358979323846 - 180.0;
	(void)range;
	sp = ((float)WIN_WIDTH / 2) - (int)(angle * ((double)WIN_WIDTH / 66));
	return (sp);
}

t_sprite_calc	calc_sprite(t_game *game, double x, double y)
{
	t_sprite_calc	calc;

	calc.distance = sqrt((game->pl.pos.x - x) * (game->pl.pos.x - x)
			+ (game->pl.pos.y - y) * (game->pl.pos.y - y));
	calc.angle = atan2(game->pl.pos.y - y, game->pl.pos.x - x);
	if (calc.angle < 0)
		calc.angle = 360 / (180.0 / PI) + calc.angle;
	calc.relative_angle = atan2(game->pl.dir.y, game->pl.dir.x);
	if (calc.relative_angle < 0)
		calc.relative_angle = 360 / (180.0 / PI) + calc.relative_angle;
	calc.true_angle = calc.angle - calc.relative_angle;
	if (calc.true_angle < 0)
		calc.true_angle = 360 / (180.0 / PI) + calc.true_angle;
	calc.range = calc.distance * cos(calc.true_angle);
	calc.range = fabs(calc.range);
	calc.starting_point = convert_angle(calc.true_angle, calc.range);
	return (calc);
}

int	list_size_sprites(t_sprite *sprites)
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

int	compare_range(t_sprite *tmp, t_sprite *tmp2, t_game *game)
{
	t_sprite_calc	calc;
	t_sprite_calc	calc2;

	calc = calc_sprite(game, tmp->x + 0.5, tmp->y + 0.5);
	calc2 = calc_sprite(game, tmp2->x + 0.5, tmp2->y + 0.5);
	if (fabs(calc.range) > fabs(calc2.range))
		return (1);
	return (0);
}
