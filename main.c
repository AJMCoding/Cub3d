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
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (game->win_ptr == NULL)
	{
		ft_error_msg("Couldn't create the Window.", game);
	}
	game->free.malloc_window = 1;
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
	//game->locations = malloc(sizeof(t_locations));
	ft_init_free(game);
	ft_init_locations(game);
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
	//ft_check_map(game);
	ft_init_mlx(game);
	ft_find_images(game);
	ft_init_win(game);
	sleep(1);
}