#include "cub3d.h"

void	ft_find_images(t_game *game)
{
	(void)game;
	game->images.north.width = 32;
	game->images.north.height = 32;
	game->images.north.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->locations.north, &game->images.north.width, &game->images.north.height);
	if (game->images.north.xpm_ptr == NULL)
		ft_error_msg("Couldn't find a sprite. Does it exist?", game);
}