#include "cub3d.h"

void	ft_init_free(t_game *game)
{
	game->free.malloc_map = 0;
	game->free.malloc_display = 0;
	game->free.malloc_window = 0;
	game->free.malloc_sprites = 0;
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
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
}