#include "cub3d_bonus.h"
#include <X11/X.h>

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
	{
		printf("Error\nMalloc error.\nCLOSED\n");
		exit (EXIT_FAILURE);
	}
	game->img.img = NULL;
	ft_init(game);
	ft_check_input(argc, argv, game);
	ft_read_map(game, argv[1]);
	ft_check_map(game);
	ft_init_mlx(game);
	ft_init_win(game);
	init_images_colours(game);
	game->frame = millitimestamp();
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr,
		&game->mouse_x, &game->mouse_y);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, close_game, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, manage_input, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask,
		manage_input_release, game);
	mlx_loop_hook(game->mlx_ptr, manage_frames, game);
	mlx_loop(game->mlx_ptr);
}
