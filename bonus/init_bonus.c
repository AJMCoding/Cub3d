#include "cub3d_bonus.h"

void	init_images_colours2(t_game *game)
{
	game->images.floor = convert_color(game->locations.floor);
	game->images.ceiling = convert_color(game->locations.ceiling);
	game->images.west_data.addr = mlx_get_data_addr(game->images.west.xpm_ptr,
			&game->images.west_data.bits_per_pixel,
			&game->images.west_data.line_length,
			&game->images.west_data.endian);
	game->images.east_data.addr = mlx_get_data_addr(game->images.east.xpm_ptr,
			&game->images.east_data.bits_per_pixel,
			&game->images.east_data.line_length,
			&game->images.east_data.endian);
	game->images.north_data.addr = mlx_get_data_addr(game->images.north.xpm_ptr,
			&game->images.north_data.bits_per_pixel,
			&game->images.north_data.line_length,
			&game->images.north_data.endian);
	game->images.south_data.addr = mlx_get_data_addr(game->images.south.xpm_ptr,
			&game->images.south_data.bits_per_pixel,
			&game->images.south_data.line_length,
			&game->images.south_data.endian);
}

void	init_images_colours(t_game *game)
{
	game->images.west.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.west, &game->images.west.width,
			&game->images.west.height);
	if (game->images.west.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the west texture.", game);
	game->images.east.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.east, &game->images.east.width,
			&game->images.east.height);
	if (game->images.east.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the east texture.", game);
	game->images.north.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.north, &game->images.north.width,
			&game->images.north.height);
	if (game->images.north.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the north texture.", game);
	game->images.south.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.south, &game->images.south.width,
			&game->images.south.height);
	if (game->images.south.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the south texture.", game);
	init_images_colours2(game);
}

void	ft_init_locations(t_game *game)
{
	game->locations.west = NULL;
	game->locations.east = NULL;
	game->locations.north = NULL;
	game->locations.south = NULL;
	game->locations.ceiling.red = -1;
	game->locations.ceiling.green = -1;
	game->locations.ceiling.blue = -1;
	game->locations.floor.red = -1;
	game->locations.floor.green = -1;
	game->locations.floor.blue = -1;
	game->images.west.xpm_ptr = NULL;
	game->images.east.xpm_ptr = NULL;
	game->images.north.xpm_ptr = NULL;
	game->images.south.xpm_ptr = NULL;
	game->free_mouse = 0;
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		ft_error_msg("Couldn't find mlx pointer.", game);
	}
}

void	ft_init_win(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
		ft_error_msg("Couldn't create the Window.", game);
}
