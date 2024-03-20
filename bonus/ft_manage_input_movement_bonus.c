#include "cub3d_bonus.h"

void	rotate_camera(t_game *g, int direction, double i)
{
	double	olddirx;
	double	oldplanex;

	olddirx = g->pl.dir.x;
	oldplanex = g->pl.plane.x;
	if (direction == 0)
	{
		g->pl.dir.x = g->pl.dir.x * cos(i) - g->pl.dir.y * sin(i);
		g->pl.dir.y = olddirx * sin(i) + g->pl.dir.y * cos(i);
		g->pl.plane.x = g->pl.plane.x * cos(i) - g->pl.plane.y * sin(i);
		g->pl.plane.y = oldplanex * sin(i) + g->pl.plane.y * cos(i);
	}
	if (direction == 1)
	{
		g->pl.dir.x = g->pl.dir.x * cos(-i) - g->pl.dir.y * sin(-i);
		g->pl.dir.y = olddirx * sin(-i) + g->pl.dir.y * cos(-i);
		g->pl.plane.x = g->pl.plane.x * cos(-i) - g->pl.plane.y * sin(-i);
		g->pl.plane.y = oldplanex * sin(-i) + g->pl.plane.y * cos(-i);
	}
}

int	check_for_move(t_game *g, int direction, char c)
{
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.080)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.080)] == c)
		return (1);
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.040)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.040)] == c)
		return (1);
	if ((int)(g->pl.pos.x + direction * g->pl.dir.x * 0.080)
	!= (int)(g->pl.pos.x) &&
	(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.080) != (int)(g->pl.pos.y))
	{
		if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.080)]
		[(int)(g->pl.pos.y)] == c && g->map.full[(int)(g->pl.pos.x)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.080)] == c)
			return (1);
	}
	return (0);
}

void	change_player_pos(t_game *g, int direction)
{
	if (check_for_move(g, direction, '1') == 1)
		return ;
	if (check_for_move(g, direction, 'P') == 1)
		return ;
	if (check_for_move(g, direction, 'A') == 1)
		return ;
	g->pl.pos.x += direction * g->pl.dir.x * 0.08;
	g->pl.pos.y += direction * g->pl.dir.y * 0.08;
}

int	check_for_move_side(t_game *g, int direction, char c)
{
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.080)]
		[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.080)] == c)
		return (1);
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.40)]
		[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.40)] == c)
		return (1);
	if ((int)(g->pl.pos.x + direction * g->pl.plane.x * 0.080)
		!= (int)(g->pl.pos.x)
		&& (int)(g->pl.pos.y + direction * g->pl.plane.y * 0.080)
		!= (int)(g->pl.pos.y))
	{
		if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.080)]
			[(int)(g->pl.pos.y)] == c && g->map.full[(int)(g->pl.pos.x)]
			[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.080)] == c)
			return (1);
	}
	return (0);
}

void	change_player_pos_side(t_game *g, int direction)
{
	if (check_for_move_side(g, direction, '1') == 1)
		return ;
	if (check_for_move_side(g, direction, 'P') == 1)
		return ;
	if (check_for_move_side(g, direction, 'A') == 1)
		return ;
	g->pl.pos.x += direction * g->pl.plane.x * 0.08;
	g->pl.pos.y += direction * g->pl.plane.y * 0.08;
}
