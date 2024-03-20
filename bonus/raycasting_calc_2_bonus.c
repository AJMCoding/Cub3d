#include "cub3d_bonus.h"

t_calc_data	pos_check(t_game *game, t_ray ray, t_calc_data data)
{
	if (game->map.full[ray.map_x][ray.map_y] == 'D')
		data = calc_door(game, ray, data);
	if (game->map.full[ray.map_x][ray.map_y] == 'P')
		save_sprite(game, ray.map_x, ray.map_y, 1);
	if (game->map.full[ray.map_x][ray.map_y] == 'A')
		save_sprite(game, ray.map_x, ray.map_y, 2);
	if (game->map.full[ray.map_x][ray.map_y] == '1')
		data.hit = 1;
	return (data);
}

t_calc_data	calculate_ray3(t_game *game, t_ray ray, t_calc_data data)
{
	if (data.door_found == 0)
	{
		data.ray_map_x = ray.map_x;
		data.ray_map_y = ray.map_y;
	}
	if (ray.num == 0)
		game->first_ray = data;
	if (ray.num == WIN_WIDTH - 1)
		game->last_ray = data;
	return (data);
}

t_calc_data	calculate_ray2(t_game *game, t_ray ray, t_calc_data data)
{
	if (ray.dir_x < 0)
	{
		data.stepx = -1;
		data.sidedistx = (game->pl.pos.x - ray.map_x) * data.deltadistx;
	}
	else
	{
		data.stepx = 1;
		data.sidedistx = (ray.map_x + 1.0 - game->pl.pos.x) * data.deltadistx;
	}
	if (ray.dir_y < 0)
	{
		data.stepy = -1;
		data.sidedisty = (game->pl.pos.y - ray.map_y) * data.deltadisty;
	}
	else
	{
		data.stepy = 1;
		data.sidedisty = (ray.map_y + 1.0 - game->pl.pos.y) * data.deltadisty;
	}
	return (data);
}

t_calc_data	calculate_ray(t_game *game, t_ray ray, t_calc_data data)
{
	data = calculate_ray2(game, ray, data);
	if (game->map.full[(int)game->pl.pos.x][(int)game->pl.pos.y] == 'A')
		save_sprite(game, (int)game->pl.pos.x, (int)game->pl.pos.y, 2);
	while (data.hit == 0)
	{
		if (data.sidedistx < data.sidedisty)
		{
			data.sidedistx += data.deltadistx;
			ray.map_x += data.stepx;
			data.side = 0;
		}
		else
		{
			data.sidedisty += data.deltadisty;
			ray.map_y += data.stepy;
			data.side = 1;
		}
		data = pos_check(game, ray, data);
	}
	data = calculate_ray3(game, ray, data);
	return (data);
}
