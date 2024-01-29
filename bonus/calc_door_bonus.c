#include "cub3d_bonus.h"
#include <X11/X.h>

int find_direction(t_ray ray, t_calc_data data)
{
	if (data.side == 0)
	{
		if (ray.dir_x < 0.5)
			return (1);
		else
			return (3);
	}
	else
	{
		if (ray.dir_y < 0.5)
			return (2);
		else
			return (4);
	}
}

t_position	calc_next_hit_pos(t_game *game, t_ray ray, t_calc_data data)
{
	//calculate position of next hit
	t_position	next_hit_pos;
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
	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 0)
		next_hit_pos.x = ray.pixel + ray.map_x;
	else
		next_hit_pos.y = ray.pixel + ray.map_y;
	if (data.side == 0)
		next_hit_pos.y = ray.map_y;
	else
		next_hit_pos.x = ray.map_x;
	return (next_hit_pos);
}

t_position	calc_current_pos(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;

	if (data.side == 1)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 1)
		current_pos.x = ray.pixel + ray.map_x;
	else
		current_pos.y = ray.pixel + ray.map_y;
	if (data.side == 1)
		current_pos.y = ray.map_y;
	else
		current_pos.x = ray.map_x;
	return (current_pos);
}

double	calculate_pos_hits_middle_of_square(t_position start_pos, t_position end_pos, t_calc_data data)
{
	double	middle_pos;

	if (data.side == 0)
	{
		middle_pos = (start_pos.y + end_pos.y) / 2;
	}
	else
	{
		middle_pos = (start_pos.x + end_pos.x) / 2;
	}
	return (middle_pos);
}

t_calc_data	calc_door(t_game *game, t_ray ray, t_calc_data data)
{
	int			i;
	t_position	next_hit_pos;
	t_position	current_pos;
	double		p;

	i = find_direction(ray, data);
	//find if we first hit the middle of the square or the side of the square
	next_hit_pos = calc_next_hit_pos(game, ray, data);
	current_pos = calc_current_pos(game, ray, data);
	//printf("next_hit_pos: %f %f\n", next_hit_pos.x, next_hit_pos.y);
	//printf("current_pos: %f %f\n", current_pos.x, current_pos.y);
	printf("i: %d\n", i);
	if (i == 2)
	{
		if (next_hit_pos.y < current_pos.y + 0.5)
			return (data);
		else
		{
			p = calculate_pos_hits_middle_of_square(next_hit_pos, current_pos, data);
			data.ray_map_x = current_pos.x + 0.5;
			data.ray_map_y = current_pos.y - p;
		}
	}
	if (i == 4)
	{
		if (next_hit_pos.y > current_pos.y + 0.5)
			return (data);
		else
		{
			p = calculate_pos_hits_middle_of_square(next_hit_pos, current_pos, data);
			data.ray_map_x = current_pos.x - 0.5;
			data.ray_map_y = current_pos.y + p;
		}
	}
	if (i == 1)
	{
		if (next_hit_pos.x > current_pos.x + 0.5)
			return (data);
		else
		{
			p = calculate_pos_hits_middle_of_square(next_hit_pos, current_pos, data);
			data.ray_map_x = current_pos.x - p;
			data.ray_map_y = current_pos.y - 0.5;
		}
	}
	else
	{
		if (next_hit_pos.x < current_pos.x + 0.5)
			return (data);
		else
		{
			p = calculate_pos_hits_middle_of_square(next_hit_pos, current_pos, data);
			data.ray_map_x = current_pos.x + p;
			data.ray_map_y = current_pos.y + 0.5;
		}
	}
	//printf("hi\n");
	data.hit = 1;
	data.door_found = 1;
	if (i == 1)
	{
		data.sidedistx += data.deltadistx / 2;
	}
	if (i == 3)
	{
		data.sidedistx -= data.deltadistx / 2;
	}
	if (i == 2)
	{
		data.sidedisty -= data.deltadisty / 2;
	}
	if (i == 4)
	{
		data.sidedisty += data.deltadisty / 2;
	}
	return (data);
}