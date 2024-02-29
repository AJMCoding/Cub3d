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
	game->images.sprite_data.addr = mlx_get_data_addr(game->images.sprite.xpm_ptr,
			&game->images.sprite_data.bits_per_pixel,
			&game->images.sprite_data.line_length,
			&game->images.sprite_data.endian);
	game->images.door_data.addr = mlx_get_data_addr(game->images.door.xpm_ptr,
			&game->images.door_data.bits_per_pixel,
			&game->images.door_data.line_length,
			&game->images.door_data.endian);
	game->images.a_sprite1_data.addr = mlx_get_data_addr(game->images.a_sprite1.xpm_ptr,
			&game->images.a_sprite1_data.bits_per_pixel,
			&game->images.a_sprite1_data.line_length,
			&game->images.a_sprite1_data.endian);
	game->images.a_sprite2_data.addr = mlx_get_data_addr(game->images.a_sprite2.xpm_ptr,
			&game->images.a_sprite2_data.bits_per_pixel,
			&game->images.a_sprite2_data.line_length,
			&game->images.a_sprite2_data.endian);		
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
	game->images.sprite.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.sprite, &game->images.sprite.width,
			&game->images.sprite.height);
	if (game->images.sprite.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the sprite texture.", game);
	game->images.door.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.door, &game->images.door.width,
			&game->images.door.height);
	if (game->images.door.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the door texture.", game);
	game->images.a_sprite1.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.a_sprite1, &game->images.a_sprite1.width,
			&game->images.a_sprite1.height);
	if (game->images.a_sprite1.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the first frame of the animated sprite.", game);
	game->images.a_sprite2.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->locations.a_sprite2, &game->images.a_sprite2.width,
			&game->images.a_sprite2.height);
	if (game->images.a_sprite2.xpm_ptr == NULL)
		ft_error_msg("Couldn't find the second frame of the animated sprite.", game);
	init_images_colours2(game);
}

void	ft_init(t_game *game)
{
	game->locations.west = NULL;
	game->locations.east = NULL;
	game->locations.north = NULL;
	game->locations.south = NULL;
	game->locations.sprite = NULL;
	game->locations.a_sprite1 = NULL;
	game->locations.a_sprite2 = NULL;
	game->locations.door = NULL;
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
	game->images.sprite.xpm_ptr = NULL;
	game->images.door.xpm_ptr = NULL;
	game->images.a_sprite1.xpm_ptr = NULL;
	game->images.a_sprite2.xpm_ptr = NULL;
	game->free_mouse = 0;
	game->input.front = 0;
	game->input.back = 0;
	game->input.left = 0;
	game->input.right = 0;
	game->input.turn_left = 0;
	game->input.turn_right = 0;
	game->sprites = NULL;
	game->doors = NULL;
	game->distances = NULL;
	game->frame_num = 0;
	game->distances = malloc(sizeof(double) * WIN_WIDTH);
	if (game->distances == NULL)
		ft_error_msg("Malloc Error", game);
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
