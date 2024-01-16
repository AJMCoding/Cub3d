#include "cub3d.h"

//NO SO WE EA F C

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

void	add_image(t_game *game, char *str, int i)
{
	
}

void	add_colour(t_game *game, char *str, int i)
{

}

void	find_sprites(t_game *game, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			if (compare_to_identifier(str, i) == 1)
				add_image(game, str, i);
			else if (compare_to_identifier(str, i) == 2)
				add_colour(game, str, i);
		}
		i++;
	}
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
	//int		i;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error_msg("The Map couldn't be opened.", game);
	str = read_map2(fd);
	close(fd);
	if (str == NULL)
		ft_error_msg("Error while reading the map.", game);
	find_sprites(game, str);
	printf("%s\n", str);
}