/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:22:08 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:22:13 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//NO SO WE EA F C

char	*ft_strjoin_free_str(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (left_str == NULL)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	if (left_str[0] != '\0')
		free(left_str);
	return (str);
}

int	ft_check_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			return (0);
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (1);
}

void	find_map(t_game *game, char *str, int i)
{
	char	*str2;
	int		tmp;

	tmp = find_map_utils(game, str, i);
	while (str[tmp] != '\0')
	{
		if ((str[tmp] == '\n' && str[tmp + 1] == '\n')
			|| (str[tmp] == '\n' && str[tmp + 1] == '\0'))
			ft_error_msg("New line in the map!", game);
		tmp++;
	}
	str2 = ft_strldup(str + i, ft_strlen(str + i));
	if (str2 == NULL)
	{
		free(str);
		ft_error_msg("Error while reading the map.", game);
	}
	game->map.full = ft_split(str2, '\n');
	if (game->map.full == NULL)
	{
		free(str);
		free(str2);
		ft_error_msg("Error while reading the map.", game);
	}
	free(str2);
}

char	*read_map2(int fd)
{
	char	*str;
	char	*buffer;
	int		length;

	length = 1;
	buffer = malloc((2) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	str = "\0";
	while (length != 0)
	{
		length = read(fd, buffer, 1);
		if (length == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[length] = '\0';
		str = ft_strjoin_free_str(str, buffer);
	}
	free(buffer);
	return (str);
}

/*
void	print_stuff(t_game *game)
{
	int p;

	printf("floor: %d %d %d\n", game->locations.floor.red,
	game->locations.floor.green, game->locations.floor.blue);
	printf("ceiling: %d %d %d\n", game->locations.ceiling.red,
	game->locations.ceiling.green, game->locations.ceiling.blue);
	printf("north: %s\n", game->locations.north);
	printf("south: %s\n", game->locations.south);
	printf("west: %s\n", game->locations.west);
	printf("east: %s\n", game->locations.east);
	p = 0;
	while (game->map.full[p] != NULL)
	{
		printf("%s\n", game->map.full[p]);
		p++;
	}
}*/

void	ft_read_map(t_game *game, char *argv)
{
	int		fd;
	int		i;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error_msg("The Map couldn't be opened.", game);
	game->str = read_map2(fd);
	i = close(fd);
	if (game->str == NULL)
		ft_error_msg("Error while reading the map.", game);
	i = find_sprites(game, game->str);
	find_map(game, game->str, i);
	free(game->str);
	game->str = NULL;
}
