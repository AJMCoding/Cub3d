#include "cub3d.h"

void	ft_init_free(t_game *game)
{
	game->free.malloc_map = 0;
	game->free.malloc_display = 0;
	game->free.malloc_window = 0;
	game->free.malloc_sprites = 0;
}

void	ft_init_locations(t_game *game)
{
	game->locations.west = NULL;
	game->locations.east = NULL;
	game->locations.north = NULL;
	game->locations.south = NULL;
	game->locations.ceiling.red = -1;
	game->locations.ceiling.green = -1;
	game->locations.ceiling.blue = -1;
	game->locations.floor.red = -1;
	game->locations.floor.green = -1;
	game->locations.floor.blue = -1;
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		ft_error_msg("Couldn't find mlx pointer.", game);
	}
	game->free.malloc_display = 1;
}

void	ft_init_win(t_game *game)
{
	//game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.rows * IMG_HEIGHT, game->map.columns * IMG_WIDTH, "so_long");
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
	{
		ft_error_msg("Couldn't create the Window.", game);
	}
	game->free.malloc_window = 1;
}

void	init_player(t_game *game)
{
	game->pl.dir.x = 0.5; // set while parsing map 
	game->pl.dir.y = 0.5; // set while parsing map
	game->pl.plane.x = 0;
	game->pl.plane.y = 0.66;
	game->pl.pos.x = 2; // set while parsing map
	game->pl.pos.y = 5; // set while parsing map
}

void	rotate_camera(t_game *game, int direction)
{
	double oldDirX;
	double rotSpeed;
	printf("hi");

	rotSpeed = 0.2;
	oldDirX = game->pl.dir.x;
	if (direction == 0)
	{
		game->pl.dir.x = game->pl.dir.x * cos(rotSpeed) - game->pl.dir.y * sin(rotSpeed);
		game->pl.dir.y = oldDirX * sin(rotSpeed) + game->pl.dir.y * cos(rotSpeed);
		printf("dir_x: %f dir_y: %f\n", game->pl.dir.x, game->pl.dir.y);
	}
	if (direction == 1)
	{
		game->pl.dir.x = game->pl.dir.x * cos(-rotSpeed) - game->pl.dir.y * sin(-rotSpeed);
		game->pl.dir.y = oldDirX * sin(-rotSpeed) + game->pl.dir.y * cos(-rotSpeed);
		printf("dir_x: %f dir_y: %f\n", game->pl.dir.x, game->pl.dir.y);
	}
}

int	manage_inputs(int keysym, t_game *game)
{
	printf("key: %d\n", keysym);
	if (keysym == PRESS_A)
		rotate_camera(game, 0);
	if (keysym == PRESS_D)
		rotate_camera(game, 1);
	if (keysym == PRESS_ESC)
		close_game(game);
	raycasting(game);
	return (0);
}

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
	{
		printf("Malloc error.\nCLOSED\n");
		exit (EXIT_FAILURE);
	}
	ft_init_free(game);
	ft_init_locations(game);
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
	//ft_check_map(game);
	ft_init_mlx(game);
	init_player(game);
	ft_find_images(game);
	ft_init_win(game);
	raycasting(game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, manage_inputs, game);
	mlx_loop(game->mlx_ptr);
}