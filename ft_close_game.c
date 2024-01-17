# include "cub3d.h"

void	free_allocated_memory(t_game *game)
{
	int	str;

	if (game->free.malloc_sprites == 1)
	{
		//destroy images
	}
	if (game->free.malloc_window == 1)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->free.malloc_display == 1)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	str = 0;
	if (game->free.malloc_map == 1)
	{
		while (game->map.full[str] != NULL)
			free(game->map.full[str++]);
		free(game->map.full);
	}
	free(game);
}

int	close_game(t_game *game)
{
	free_allocated_memory(game);
	printf("CLOSED\n");
	exit (EXIT_FAILURE);
}

int	ft_error_msg(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	close_game(game);
	exit (EXIT_FAILURE);
}