#include "cub3d.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
	{
		printf("Malloc error.\nCLOSED\n");
		exit (EXIT_FAILURE);
	}
	game->img.img = NULL;
	ft_init_locations(game);
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
	ft_check_map(game);
	//ft_validpath_check(game);
	ft_init_mlx(game);
	ft_init_win(game);
	init_images_colours(game);
	raycasting(game);
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr,
		&game->mouse_x, &game->mouse_y);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, manage_input, game);
	mlx_loop_hook(game->mlx_ptr, update_frame, game);
	mlx_loop(game->mlx_ptr);
}
