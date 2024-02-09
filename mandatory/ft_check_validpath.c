#include "cub3d.h"

int ft_strlen_so_long(const char *s)
{
	int len = 0;
	while (s[len] != '\0')
		len++;
	return len;
}

int is_reachable(char **map, int x, int y, int rows)
{
	if (x < 0 || y < 0 || x >= ft_strlen_so_long(*map) || y >= rows
		|| map[y][x] == 'X' || map[y][x] == '1')
	{
		return 1;
	}
	map[y][x] = 'X';
	is_reachable(map, x - 1, y, rows);
	is_reachable(map, x + 1, y, rows);
	is_reachable(map, x, y - 1, rows);
	is_reachable(map, x, y + 1, rows);
	return 0;
}

void ft_validpath_check(t_game *list)
{
	int i;
	int j;
	int width;
	int height;


	i = 0;
	j = 0;
	width = ft_strlen_so_long(list->map.full[0]);
	height = ft_strlen_so_long(list->map.full[1]);
	is_reachable(list->map.full, 0, 0,height);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (list->map.full[i][j] != 'X'
				&& list->map.full[i][j] != '1')
				{
					ft_putstr_fd("Error\nMap is not valid.\n", 2);
					exit (EXIT_FAILURE);
				}
			j++;
		}
		i++;
	}
}