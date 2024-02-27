#include "cub3d_bonus.h"
#include <stdio.h>

t_ray	calculate_ray_angle(t_game *game, int rays)
{
	t_ray	ray;
	double	camera;
	//double	x;

	camera = 2 * rays / (double)WIN_WIDTH - 1;
	ray.dir_x = game->pl.dir.x + game->pl.plane.x * camera;
	ray.dir_y = game->pl.dir.y + game->pl.plane.y * camera;
	ray.true_dir_x = ray.dir_x / ray.dir_y;
	ray.true_dir_y = ray.dir_y / ray.dir_x;
/* 	if (rays == 0)
		printf("x:%f y:%f \n", game->pl.dir.x, game->pl.dir.y); */
	ray.true_dir_y = ray.dir_x / ray.dir_y;
	ray.true_dir_x = ray.dir_y / ray.dir_x;
/* 	if (rays == 0)
		printf("x:%f y:%f \n", ray.true_dir_x, ray.true_dir_y); */
	//ray.true_dir_x = 1 + (ray.dir_y * ray.dir_y) / (ray.dir_x * ray.dir_x);
	//ray.true_dir_y = 1 + (ray.dir_x * ray.dir_x) / (ray.dir_y * ray.dir_y);
	ray.map_x = (int)game->pl.pos.x;
	ray.map_y = (int)game->pl.pos.y;
	ray.num = rays;
	return (ray);
}

void	put_part_of_texture(t_ray ray, int start, int x_at_wall, t_game *game)
{
	int	height;
	int	color;

	height = (int)((WIN_HEIGHT / ray.distance) * 0.8);
	color = 0;
	if (ray.door_found == 1)
		color = my_mlx_pixel_get(&game->images.north_data,
				(x_at_wall / (double)height) * 64, (int)64 * ray.pixel);
	else if (ray.direction == 1)
		color = my_mlx_pixel_get(&game->images.north_data,
				(x_at_wall / (double)height) * 64, (int)64 * ray.pixel);
	else if (ray.direction == 2)
		color = my_mlx_pixel_get(&game->images.east_data,
				(x_at_wall / (double)height) * 64, (int)64 * ray.pixel);
	else if (ray.direction == 3)
		color = my_mlx_pixel_get(&game->images.south_data,
				(x_at_wall / (double)height) * 64, (int)64 * ray.pixel);
	else if (ray.direction == 4)
		color = my_mlx_pixel_get(&game->images.west_data,
				(x_at_wall / (double)height) * 64, (int)64 * ray.pixel);
	my_mlx_pixel_put(&game->img, ray.num, start, color);
}

void	draw_wall(t_ray ray, t_game *game)
{
	int	height;
	int	start;
	int	end;
	int	i;

	i = 0;
	height = (int)((WIN_HEIGHT / ray.distance) * 0.8);
	start = -height / 2 + WIN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + WIN_HEIGHT / 2;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	if (height > WIN_HEIGHT)
	{
		i = (height - WIN_HEIGHT) / 2;
	}
	while (start < end)
	{
		put_part_of_texture(ray, start, height - i, game);
		start++;
		i++;
	}
}

void	draw_floor_ceiling(t_game *game, t_data2 img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(&img, x, y, game->images.floor);
			else
				my_mlx_pixel_put(&img, x, y, game->images.ceiling);
			y++;
		}
		x++;
	}
}

void    free_game_sprites(t_game *game)
{
	t_sprite *tmp;
	t_sprite *tmp2;

	if (game->sprites == NULL)
		return ;
	tmp = game->sprites;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	raycasting(t_game *game)
{
	int		rays;
	t_ray	ray;

	rays = 0;
	if (game->img.img != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	game->img.img = NULL;
	game->img.img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	free_game_sprites(game);
	game->sprites = NULL;
	draw_floor_ceiling(game, game->img);
	while (rays < WIN_WIDTH)
	{
		ray = calculate_ray_angle(game, rays);
		ray = calculate_distance_to_wall(game, ray);
		draw_wall(ray, game);
		if (ray.num == 0)	
			printf("ray %f\n", ray.distance);
		draw_sprites(game);
		rays ++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}
