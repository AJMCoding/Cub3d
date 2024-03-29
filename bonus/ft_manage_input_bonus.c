/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_input_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:17:40 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:17:41 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* void	rotate_camera(t_game *g, int direction, double i)
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
} */

int	manage_input(int keysym, t_game *game)
{
	if (keysym == PRESS_LEFT)
		game->input.turn_left = 1;
	if (keysym == PRESS_RIGHT)
		game->input.turn_right = 1;
	if (keysym == PRESS_W)
		game->input.front = 1;
	if (keysym == PRESS_S)
		game->input.back = 1;
	if (keysym == PRESS_A)
		game->input.left = 1;
	if (keysym == PRESS_D)
		game->input.right = 1;
	if (keysym == PRESS_ESC)
		close_game(game);
	if (keysym == PRESS_Q)
	{
		if (game->free_mouse == 0)
			game->free_mouse = 1;
		else
			game->free_mouse = 0;
	}
	return (0);
}

int	manage_input_release(int keysym, t_game *game)
{
	if (keysym == PRESS_LEFT)
		game->input.turn_left = 0;
	if (keysym == PRESS_RIGHT)
		game->input.turn_right = 0;
	if (keysym == PRESS_W)
		game->input.front = 0;
	if (keysym == PRESS_S)
		game->input.back = 0;
	if (keysym == PRESS_A)
		game->input.left = 0;
	if (keysym == PRESS_D)
		game->input.right = 0;
	return (0);
}

int	manage_frames(t_game *game)
{
	long long	now;
	long long	diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->frame;
	if (diff_millisecs > 16)
	{
		game->frame_num++;
		game->frame = now;
		update_frame(game);
	}
	return (0);
}

void	update_doors(t_game *game)
{
	t_door	*tmp;

	tmp = game->doors;
	while (tmp != NULL)
	{
		if ((tmp->x < (int)game->pl.pos.x + 3
				&& tmp->x > (int)game->pl.pos.x - 3)
			&& (tmp->y < (int)game->pl.pos.y + 3
				&& tmp->y > (int)game->pl.pos.y - 3))
		{
			tmp->open += -0.05;
			if (tmp->open < 0)
				tmp->open = 0;
		}
		else
		{
			tmp->open += 0.05;
			if (tmp->open > 1)
				tmp->open = 1;
		}
		tmp = tmp->next;
	}
}

/* void	movements(t_game *game)
{
	if (game->input.turn_left == 1 && game->input.turn_right == 0)
		rotate_camera(game, 0, 0.03);
	if (game->input.turn_left == 0 && game->input.turn_right == 1)
		rotate_camera(game, 1, 0.03);
	if (game->input.front == 1 && game->input.back == 0)
		change_player_pos(game, 1);
	if (game->input.front == 0 && game->input.back == 1)
		change_player_pos(game, -1);
	if (game->input.left == 1 && game->input.right == 0)
		change_player_pos_side(game, -1);
	if (game->input.left == 0 && game->input.right == 1)
		change_player_pos_side(game, 1);
} */

int	update_frame(t_game *game)
{
	int	old;

	old = game->mouse_x;
	update_doors(game);
	mlx_mouse_get_pos(game->mlx_ptr,
		game->win_ptr, &game->mouse_x, &game->mouse_y);
	if (old < game->mouse_x && game->free_mouse == 0)
		rotate_camera(game, 1, fabs((double)(game->mouse_x - old) * 0.001));
	else if (old > game->mouse_x && game->free_mouse == 0)
		rotate_camera(game, 0, (double)(old - game->mouse_x) * 0.001);
	if (game->free_mouse == 0)
		mlx_mouse_move(game->mlx_ptr, game->win_ptr,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->mouse_x = WIN_WIDTH / 2;
	movements(game);
	raycasting(game);
	return (0);
}
