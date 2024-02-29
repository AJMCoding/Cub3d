#include "cub3d_bonus.h"

int	is_valid(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D' || c == 'P' || c == 'A')
		return (1);
	return (0);
}

int	check_surrounded3(t_game *game, int i, int j)
{
	int	k;

	k = 0;
	while (game->map.full[i - 1][k] != '\0' && k <= j)
	{
		if (k == j && is_valid(game->map.full[i - 1][k]) == 0)
			return (0);
		k++;
		if (game->map.full[i - 1][k] == '\0' && k -1 != j)
			return (0);
	}
	return (1);
}

int	check_surrounded2(t_game *game, int i, int j)
{
	int	k;

	if (game->map.full[i + 1] == NULL)
		return (0);
	if (j <= 0 || i <= 0)
		return (0);
	if (is_valid(game->map.full[i][j + 1]) == 0
		|| is_valid(game->map.full[i][j - 1]) == 0)
		return (0);
	k = 0;
	while (game->map.full[i + 1][k] != '\0' && k <= j)
	{
		if (k == j && is_valid(game->map.full[i + 1][k]) == 0)
			return (0);
		k++;
		if (game->map.full[i + 1][k] == '\0' && k -1 != j)
			return (0);
	}
	k = check_surrounded3(game, i, j);
	if (k == 0)
		return (0);
	return (1);
}

int	walls_correct_around_door(t_game *game, int i, int j)
{
	int	k;

	k = 0;
	if (game->map.full[i][j + 1] == '1' && game->map.full[i][j - 1] == '1')
		k += 1;
	if (game->map.full[i + 1][j] == '1' && game->map.full[i - 1][j] == '1')
		k += 1;
	if (k == 0)
		return (0);
	return (1);
}

void	check_surrounded(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.full[i] != NULL)
	{
		j = 0;
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == '0' || game->map.full[i][j] == 'W'
			|| game->map.full[i][j] == 'E' || game->map.full[i][j] == 'N'
			|| game->map.full[i][j] == 'S' || game->map.full[i][j] == 'D')
			{
				if (check_surrounded2(game, i, j) == 0)
					ft_error_msg("The map is not surrounded by walls.", game);
			}
			if (game->map.full[i][j] == 'D')
				if (walls_correct_around_door(game, i, j) == 0)
					ft_error_msg("A Door is placed in a forbidden way.", game);
			j++;
		}
		i++;
	}
}
