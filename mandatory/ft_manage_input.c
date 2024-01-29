#include "cub3d.h"
#include <X11/X.h>

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

void	change_player_pos(t_game *g, int direction)
{
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.21)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.21)] == '1')
		return ;
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.10)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.10)] == '1')
		return ;
	if ((int)(g->pl.pos.x + direction * g->pl.dir.x * 0.21)
	!= (int)(g->pl.pos.x) &&
	(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.21) != (int)(g->pl.pos.y))
	{
		if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.dir.x * 0.21)]
		[(int)(g->pl.pos.y)] == '1' && g->map.full[(int)(g->pl.pos.x)]
		[(int)(g->pl.pos.y + direction * g->pl.dir.y * 0.21)] == '1')
			return ;
	}
	g->pl.pos.x += direction * g->pl.dir.x * 0.2;
	g->pl.pos.y += direction * g->pl.dir.y * 0.2;
}

void	change_player_pos_side(t_game *g, int direction)
{
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.21)]
		[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.21)] == '1')
		return ;
	if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.10)]
		[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.10)] == '1')
		return ;
	if ((int)(g->pl.pos.x + direction * g->pl.plane.x * 0.21)
		!= (int)(g->pl.pos.x)
		&& (int)(g->pl.pos.y + direction * g->pl.plane.y * 0.21)
		!= (int)(g->pl.pos.y))
	{
		if (g->map.full[(int)(g->pl.pos.x + direction * g->pl.plane.x * 0.21)]
			[(int)(g->pl.pos.y)] == '1' && g->map.full[(int)(g->pl.pos.x)]
			[(int)(g->pl.pos.y + direction * g->pl.plane.y * 0.21)] == '1')
			return ;
	}
	g->pl.pos.x += direction * g->pl.plane.x * 0.2;
	g->pl.pos.y += direction * g->pl.plane.y * 0.2;
}

int	manage_input(int keysym, t_game *game)
{
	if (keysym == PRESS_LEFT)
		rotate_camera(game, 0, 0.2);
	if (keysym == PRESS_RIGHT)
		rotate_camera(game, 1, 0.2);
	if (keysym == PRESS_W)
		change_player_pos(game, 1);
	if (keysym == PRESS_S)
		change_player_pos(game, -1);
	if (keysym == PRESS_A)
		change_player_pos_side(game, -1);
	if (keysym == PRESS_D)
		change_player_pos_side(game, 1);
	if (keysym == PRESS_ESC)
		close_game(game);
	return (0);
}

int	update_frame(t_game *game)
{
	raycasting(game);
	return (0);
}
