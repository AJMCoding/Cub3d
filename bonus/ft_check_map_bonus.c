#include "cub3d_bonus.h"

void	update_direction2(t_game *game, char direction)
{
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

void	update_direction(t_game *game, char direction, int i, int j)
{
	game->pl.pos.x = i + 0.5;
	game->pl.pos.y = j + 0.5;
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
	update_direction2(game, direction);
}

void	check_parameters(t_game *game, int i, int j)
{
	int	found;

	i = 0;
	found = 0;
	while (game->map.full[i] != NULL)
	{
		j = 0;
		while (game->map.full[i][j] != '\0')
		{
			if (game->map.full[i][j] == 'W' || game->map.full[i][j] == 'E'
				|| game->map.full[i][j] == 'N' || game->map.full[i][j] == 'S')
			{
				update_direction(game, game->map.full[i][j], i, j);
				found++;
			}
			if (char_part_of_map(game->map.full[i][j]) == 0)
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

void	ft_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_parameters(game, i, j);
	check_surrounded(game);
}
