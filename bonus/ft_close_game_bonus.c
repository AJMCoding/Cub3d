#include "cub3d_bonus.h"

void	free_allocated_memory2(t_game *game)
{
	if (game->locations.north != NULL)
		free(game->locations.north);
	if (game->locations.south != NULL)
		free(game->locations.south);
	if (game->locations.east != NULL)
		free(game->locations.east);
	if (game->locations.west != NULL)
		free(game->locations.west);
	if (game->images.west.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.west.xpm_ptr);
	if (game->images.east.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.east.xpm_ptr);
	if (game->images.north.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.north.xpm_ptr);
	if (game->images.south.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.south.xpm_ptr);
}

void	free_allocated_memory(t_game *game)
{
	int	str;

	free_allocated_memory2(game);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img.img != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	}
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	str = 0;
	if (game->map.full != NULL)
	{
		while (game->map.full[str] != NULL)
			free(game->map.full[str++]);
		free(game->map.full);
	}
	free_game_sprites(game);
	free(game);
	if (game->distances != NULL)
		free(game->distances);	
}

int	close_game(t_game *game)
{
	free_allocated_memory(game);
	printf("CLOSED\n");
	exit (EXIT_SUCCESS);
}

int	close_game_error(t_game *game)
{
	free_allocated_memory(game);
	printf("CLOSED\n");
	exit (EXIT_FAILURE);
}

void	ft_error_msg(char *message, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	close_game_error(game);
}
