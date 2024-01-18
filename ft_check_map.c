#include "cub3d.h"

void	update_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->pl.dir.x = -1.0;
		game->pl.dir.y = 0.0;
		game->pl.plane.x = 0.0;
		game->pl.plane.y = 0.66;
	}
	if (direction == 'S')
	{
		game->pl.dir.x = 1.0;
		game->pl.dir.y = 0.0;
		game->pl.plane.x = 0.0;
		game->pl.plane.y = -0.66;
	}
	if (direction == 'W')
	{
		game->pl.dir.x = 0.0;
		game->pl.dir.y = -1.0;
		game->pl.plane.x = -0.66;
		game->pl.plane.y = 0.0;
	}
	if (direction == 'E')
	{
		game->pl.dir.x = 0.0;
		game->pl.dir.y = 1.0;
		game->pl.plane.x = 0.66;
		game->pl.plane.y = 0.0;
	}
}

void	check_parameters(t_game *game)
{
	int found;
	int i;
	int j;
	
	i = 0;
	found = 0;
	while (game->map.full[i] != NULL)
	{
		j  = 0;
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == 'W' || game->map.full[i][j] == 'E' || game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S')
			{
				game->pl.pos.x = i;
				game->pl.pos.y = j;
				update_direction(game, game->map.full[i][j]);
				found++;
			}
			if (game->map.full[i][j] != '0' && game->map.full[i][j] != '1' && game->map.full[i][j] != '2' && game->map.full[i][j] != 'W' && game->map.full[i][j] != 'E' && game->map.full[i][j] != 'N' && game->map.full[i][j] != 'S' && game->map.full[i][j] != ' ')
				ft_error_msg("The map contains invalid characters.", game);
			j++;
		}
		i++;
	}
	if (found > 1)
		ft_error_msg("The map has to many players.", game);
	if (found == 0)
		ft_error_msg("The map has no player.", game);
}

int	check_surrounded2(t_game *game, int i, int j)
{
	int k;

	k = 0;
	if (game->map.full[i][j - 1] == ' ' || game->map.full[i][j + 1] == ' ')
		return (0);
	if (game->map.full[i + 1] == NULL)
		return (0);
	if (i == 0)
		return (0);
	while (game->map.full[i + 1][k] != '\0' && k <= j)
	{
		if (k == j && game->map.full[i + 1][k] == ' ')
			return (0);
		if (k == j && game->map.full[i + 1][k] != ' ')
			return (1);
		k++;
		if (game->map.full[i + 1][k] == '\0')
			return(0);
	}
	k = 0;
	while (game->map.full[i - 1][k] != '\0' && k <= j)
	{
		if (k == j && game->map.full[i - 1][k] == ' ')
			return (0);
		if (k == j && game->map.full[i - 1][k] != ' ')
			return (1);
		k++;
		if (game->map.full[i - 1][k] == '\0')
			return (0);
	}
	return (1);
}

void	check_surrounded(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.full[i] != NULL)
	{
		j = 0;
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == '0' || game->map.full[i][j] == 'W' || game->map.full[i][j] == 'E' || game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S')
			{
				if (check_surrounded2(game, i, j) == 0)
					ft_error_msg("The map is not surrounded by walls.", game);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_map(t_game *game)
{
	check_parameters(game);
	check_surrounded(game);
}

