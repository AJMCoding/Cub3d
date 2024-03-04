#include "cub3d_bonus.h"

void	free_game_doors(t_game *game)
{
	t_door	*tmp;
	t_door	*tmp2;

	if (game->doors == NULL)
		return ;
	tmp = game->doors;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	free_allocated_memory_3(t_game *game)
{
	free_game_sprites(game);
	free_game_doors(game);
	if (game->locations.north != NULL)
		free(game->locations.north);
	if (game->locations.south != NULL)
		free(game->locations.south);
	if (game->locations.east != NULL)
		free(game->locations.east);
	if (game->locations.west != NULL)
		free(game->locations.west);
	if (game->locations.sprite != NULL)
		free(game->locations.sprite);
	if (game->locations.door != NULL)
		free(game->locations.door);
	if (game->locations.a_sprite1 != NULL)
		free(game->locations.a_sprite1);
	if (game->locations.a_sprite2 != NULL)
		free(game->locations.a_sprite2);
}

void	free_allocated_memory2(t_game *game)
{
	free_allocated_memory_3(game);
	if (game->images.west.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.west.xpm_ptr);
	if (game->images.east.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.east.xpm_ptr);
	if (game->images.north.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.north.xpm_ptr);
	if (game->images.south.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.south.xpm_ptr);
	if (game->images.sprite.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.sprite.xpm_ptr);
	if (game->images.door.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.door.xpm_ptr);
	if (game->images.a_sprite1.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.a_sprite1.xpm_ptr);
	if (game->images.a_sprite2.xpm_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->images.a_sprite2.xpm_ptr);
}

void	free_allocated_memory(t_game *game)
{
	int	str;

	free_allocated_memory2(game);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img.img != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	}
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	str = 0;
	if (game->map.full != NULL)
	{
		while (game->map.full[str] != NULL)
			free(game->map.full[str++]);
		free(game->map.full);
	}
	if (game->distances != NULL)
		free(game->distances);
	free(game);
}
