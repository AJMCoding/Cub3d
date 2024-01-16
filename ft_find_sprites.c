#include "cub3d.h"

int	ft_atoi_image(char *nptr, int i)
{
	long long int	result;

	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > 255)
			return (256);
		result = result * 10 + (nptr[i++] - '0');
	}
	return (result);
}

int	compare_to_identifier(char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'F' && str[i + 1] == ' ')
		return (2);
	if (str[i] == 'C' && str[i + 1] == ' ')
		return (2);
	return (0);
}

int	add_colour2(int mode, int value, int pos, t_game *game)
{
	/*printf("mode: %d\n", mode);
	printf("pos: %d\n", pos);
	printf("value: %d\n", value);*/
	if (mode == 1)
	{
		if (pos == 0)
			game->locations.floor.red = value;
		if (pos == 1)
			game->locations.floor.green = value;
		if (pos == 2)
			game->locations.floor.blue = value;
	}
	if (mode == 2)
	{
		if (pos == 0)
			game->locations.ceiling.red = value;
		if (pos == 1)
			game->locations.ceiling.green = value;
		if (pos == 2)
			game->locations.ceiling.blue = value;
	}
	return (pos + 1);
}

int	find_number_length(char *str, int i)
{
	int	length;

	length = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 1)
			length++;
		else
			break ;
		i++;
	}
	length++;
	//printf("length: %d\n", length);
	return (length);
} 

int	add_colour(t_game *game, char *str, int i)
{
	int mode;
	int	num;

	mode = 0;
	num = 0;
	if (str[i] == 'F' && str[i + 1] == ' ')
		mode = 1;
	if (str[i] == 'C' && str[i + 1] == ' ')
		mode = 2;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 1 && num < 3)
		{
			if (ft_atoi_image(str, i) != 256)
				num = add_colour2(mode, ft_atoi_image(str, i), num, game);
			else
				ft_error_msg("a colour is not valid.", game);
			i += find_number_length(str, i);
		}
		else
			break ;
	}
	return(i);
}

int	find_image_type(char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (1);
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		return (2);
	if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		return (3);
	if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		return (4);
	return (0);
}

int	add_image(t_game *game, char *str, int i)
{
	int	mode;
	(void) game;
	int j;

	j = 0;
	mode = find_image_type(str, i);
	i += 2;
	while (str[i] == ' ')
		i++;
	while (str[i + j] != '\0' && str[i + j] != '\n' && str[i + j] != ' ' && str[i + j] != '\t')
		j++;
	if (mode == 1)
		game->locations.north = ft_strldup(str + i, j);
	if (mode == 2)
		game->locations.south = ft_strldup(str + i, j);
	if (mode == 3)
		game->locations.west = ft_strldup(str + i, j);
	if (mode == 4)
		game->locations.east = ft_strldup(str + i, j);
	return (i + j);
}

void	check_all_found_error(t_game *game)
{
	if (game->locations.north == NULL)
		ft_error_msg("The north image is missing.", game);
	if (game->locations.south == NULL)
		ft_error_msg("The south image is missing.", game);
	if (game->locations.west == NULL)
		ft_error_msg("The west image is missing.", game);
	if (game->locations.east == NULL)
		ft_error_msg("The east image is missing.", game);
	if (game->locations.ceiling.red == -1 || game->locations.ceiling.green == -1 || game->locations.ceiling.blue == -1)
		ft_error_msg("The ceiling colour is missing.", game);
	if (game->locations.floor.red == -1 || game->locations.floor.green == -1 || game->locations.floor.blue == -1)
		ft_error_msg("The floor colour is missing.", game);
}

int		check_all_found(t_game *game)
{
	if (game->locations.north != NULL && game->locations.south != NULL 
		&& game->locations.west != NULL && game->locations.east != NULL 
		&& game->locations.ceiling.red != -1 && game->locations.ceiling.green != -1 && game->locations.ceiling.blue != -1 
		&& game->locations.floor.red != -1 && game->locations.floor.green != -1 && game->locations.floor.blue != -1)
		return (1);
	return (0);
}

int	find_sprites(t_game *game, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n' || i == 0)
		{
			if (str[i] == '\n')
				i++;
			if (compare_to_identifier(str, i) == 1)
				add_image(game, str, i);
			else if (compare_to_identifier(str, i) == 2)
				add_colour(game, str, i);
		}
		i++;
		if (check_all_found(game) == 1)
			break ;
	}
	check_all_found_error(game);
	while (str[i] != '\n')
		i++;
	return (i);
}