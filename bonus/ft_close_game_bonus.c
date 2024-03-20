#include "cub3d_bonus.h"

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
