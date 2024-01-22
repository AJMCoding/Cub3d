#include "cub3d.h"

void	rotate_camera(t_game *game, int direction)
{
	double oldDirX;
	double oldPlaneX;
	double rotSpeed;
	//printf("hi");

	rotSpeed = 0.1;
	oldDirX = game->pl.dir.x;
	oldPlaneX = game->pl.plane.x;
	if (direction == 0)
	{
		game->pl.dir.x = game->pl.dir.x * cos(rotSpeed) - game->pl.dir.y * sin(rotSpeed);
		game->pl.dir.y = oldDirX * sin(rotSpeed) + game->pl.dir.y * cos(rotSpeed);
		game->pl.plane.x = game->pl.plane.x * cos(rotSpeed) - game->pl.plane.y * sin(rotSpeed);
		game->pl.plane.y = oldPlaneX * sin(rotSpeed) + game->pl.plane.y * cos(rotSpeed);
		//printf("dir_x: %f dir_y: %f\n", game->pl.plane.x, game->pl.plane.y);
	}
	if (direction == 1)
	{
		game->pl.dir.x = game->pl.dir.x * cos(-rotSpeed) - game->pl.dir.y * sin(-rotSpeed);
		game->pl.dir.y = oldDirX * sin(-rotSpeed) + game->pl.dir.y * cos(-rotSpeed);
		game->pl.plane.x = game->pl.plane.x * cos(-rotSpeed) - game->pl.plane.y * sin(-rotSpeed);
		game->pl.plane.y = oldPlaneX * sin(-rotSpeed) + game->pl.plane.y * cos(-rotSpeed);
		//printf("dir_x: %f dir_y: %f\n", game->pl.dir.x, game->pl.dir.y);
	}
}

void	change_player_pos(t_game *game, int direction)
{
	if (game->map.full[(int)(game->pl.pos.x + direction * game->pl.dir.x * 0.21)][(int)(game->pl.pos.y + direction * game->pl.dir.y * 0.21)] == '1')
		return ;
	if (game->map.full[(int)(game->pl.pos.x + direction * game->pl.dir.x * 0.10)][(int)(game->pl.pos.y + direction * game->pl.dir.y * 0.10)] == '1')
		return ;
	game->pl.pos.x += direction * game->pl.dir.x * 0.2;
	game->pl.pos.y += direction * game->pl.dir.y * 0.2;
	//printf("pos_x: %f pos_y: %f\n", game->pl.pos.x, game->pl.pos.y);
}

int	manage_input(int keysym, t_game *game)
{
	//printf("key: %d\n", keysym);
	if (keysym == PRESS_A)
		rotate_camera(game, 0);
	if (keysym == PRESS_D)
		rotate_camera(game, 1);
	if (keysym == PRESS_W)
		change_player_pos(game, 1);
	if (keysym == PRESS_S)
		change_player_pos(game, -1);
	if (keysym == PRESS_ESC)
		close_game(game);
	raycasting(game);
	return (0);
}