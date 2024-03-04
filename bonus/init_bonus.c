#include "cub3d_bonus.h"

void	ft_init2(t_game *game)
{
	game->images.sprite.xpm_ptr = NULL;
	game->images.door.xpm_ptr = NULL;
	game->images.a_sprite1.xpm_ptr = NULL;
	game->images.a_sprite2.xpm_ptr = NULL;
	game->free_mouse = 0;
	game->input.front = 0;
	game->input.back = 0;
	game->input.left = 0;
	game->input.right = 0;
	game->input.turn_left = 0;
	game->input.turn_right = 0;
	game->sprites = NULL;
	game->doors = NULL;
	game->distances = NULL;
	game->frame_num = 0;
	game->distances = malloc(sizeof(double) * WIN_WIDTH);
	if (game->distances == NULL)
		ft_error_msg("Malloc Error", game);
}

void	ft_init(t_game *game)
{
	game->locations.west = NULL;
	game->locations.east = NULL;
	game->locations.north = NULL;
	game->locations.south = NULL;
	game->locations.sprite = NULL;
	game->locations.a_sprite1 = NULL;
	game->locations.a_sprite2 = NULL;
	game->locations.door = NULL;
	game->locations.ceiling.red = -1;
	game->locations.ceiling.green = -1;
	game->locations.ceiling.blue = -1;
	game->locations.floor.red = -1;
	game->locations.floor.green = -1;
	game->locations.floor.blue = -1;
	game->images.west.xpm_ptr = NULL;
	game->images.east.xpm_ptr = NULL;
	game->images.north.xpm_ptr = NULL;
	game->images.south.xpm_ptr = NULL;
	ft_init2(game);
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		ft_error_msg("Couldn't find mlx pointer.", game);
	}
}

void	ft_init_win(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
		ft_error_msg("Couldn't create the Window.", game);
}
