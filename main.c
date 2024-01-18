#include "cub3d.h"

void	ft_init_free(t_game *game)
{
	game->free.malloc_map = 0;
	game->free.malloc_display = 0;
	game->free.malloc_window = 0;
	game->free.malloc_sprites = 0;
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
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		ft_error_msg("Couldn't find mlx pointer.", game);
	}
	game->free.malloc_display = 1;
}

void	ft_init_win(t_game *game)
{
	//game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.rows * IMG_HEIGHT, game->map.columns * IMG_WIDTH, "so_long");
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
	{
		ft_error_msg("Couldn't create the Window.", game);
	}
	game->free.malloc_window = 1;
}

int	convert_color(t_colour color)
{
	int rgb;

	rgb = color.red;
	rgb = (rgb << 8) + color.green;
	rgb = (rgb << 8) + color.blue;
	return (rgb);
}



void	init_images_colours(t_game *game)
{
	game->images.floor = convert_color(game->locations.floor);
	game->images.ceiling = convert_color(game->locations.ceiling);
	game->images.west.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, 
	game->locations.west , &game->images.west.width, &game->images.west.height);
	if (game->images.west.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the west texture.", game);
	game->images.east.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, 
	game->locations.east , &game->images.east.width, &game->images.east.height);
	if (game->images.east.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the east texture.", game);
	game->images.north.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
	game->locations.north , &game->images.north.width, &game->images.north.height);
	if (game->images.north.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the north texture.", game);
	game->images.south.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
	game->locations.south , &game->images.south.width, &game->images.south.height);
	if (game->images.south.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the south texture.", game);
}

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
	{
		printf("Malloc error.\nCLOSED\n");
		exit (EXIT_FAILURE);
	}
	ft_init_free(game);
	ft_init_locations(game);
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
	ft_check_map(game);
	ft_init_mlx(game);
	ft_init_win(game);
	init_images_colours(game);
	raycasting(game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, manage_input, game);
	mlx_loop(game->mlx_ptr);
}