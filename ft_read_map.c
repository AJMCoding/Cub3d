#include "cub3d.h"
#include "libft/libft.h"

//NO SO WE EA F C

void	find_map(t_game *game, char *str, int i)
{
	char *str2;
	while (str[i] != '\0')
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			break ;
		i++;
	}
	while (str[i] != '\n')
		i--;
	str2 = ft_strldup(str + i, ft_strlen(str + i));
	game->map.full = ft_split(str2, '\n');
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
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

void	ft_read_map(t_game *game, char *argv)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error_msg("The Map couldn't be opened.", game);
	str = read_map2(fd);
	close(fd);
	if (str == NULL)
		ft_error_msg("Error while reading the map.", game);
	i = find_sprites(game, str);
	find_map(game, str, i);
	
	printf("floor: %d %d %d\n", game->locations.floor.red, game->locations.floor.green, game->locations.floor.blue);
	printf("ceiling: %d %d %d\n", game->locations.ceiling.red, game->locations.ceiling.green, game->locations.ceiling.blue);
	printf("north: %s\n", game->locations.north);
	printf("south: %s\n", game->locations.south);
	printf("west: %s\n", game->locations.west);
	printf("east: %s\n", game->locations.east);
	int p = 0;
	while (game->map.full[p] != NULL)
	{
		printf("%s\n", game->map.full[p]);
		p++;
	}
}