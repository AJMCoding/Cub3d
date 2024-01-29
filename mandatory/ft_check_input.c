#include "cub3d.h"

void	ft_check_input(int argc, char **argv, t_game *game)
{
	char	*str;
	int		length;
	int		i;

	if (argc > 2)
		ft_error_msg("Too many arguments.", game);
	if (argc < 2)
		ft_error_msg("The Map file is missing.", game);
	str = ".cub";
	length = ft_strlen(argv[1]) - 4;
	i = 0;
	while (argv[1][length + i])
	{
		if (argv[1][length + i] != str[i])
			ft_error_msg("The Map file is not of type .ber", game);
		i++;
	}
}
