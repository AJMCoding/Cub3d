#include "cub3d_bonus.h"

t_position	calc_current_pos(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;

	if (data.side == 0)
	{
		ray.distance = (data.sidedistx - data.deltadistx);
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
		ray.pixel -= floor((ray.pixel));
		current_pos.y = ray.pixel + ray.map_y;
		if (data.stepx < 0)
			current_pos.x = ray.map_x + 1;
		else
			current_pos.x = ray.map_x;
	}
	else
	{
		ray.distance = (data.sidedisty - data.deltadisty);
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
		ray.pixel -= floor((ray.pixel));
		current_pos.x = ray.pixel + ray.map_x;
		if (data.stepy < 0)
			current_pos.y = ray.map_y + 1;
		else
			current_pos.y = ray.map_y;
	}
	return (current_pos);
}

int	ray_hits_door_2(t_simray simray, t_calc_data data,
						t_game *game, t_position is)
{
	if (data.side == 1 && data.stepy < 0)
	{
		game->door_coord_x = (int)simray.pos_x;
		game->door_coord_y = (int)simray.pos_y - 1;
		game->pixel = is.x - floor(is.x);
		if (is.x > (int)simray.pos_x && is.x < (int)simray.pos_x + 1)
			return (1);
	}
	if (data.side == 1 && data.stepy > 0)
	{
		game->door_coord_x = (int)simray.pos_x;
		game->door_coord_y = (int)simray.pos_y;
		game->pixel = is.x - floor(is.x);
		if (is.x > (int)simray.pos_x && is.x < (int)simray.pos_x + 1)
			return (1);
	}
	return (0);
}

int	ray_hits_door(t_simray	simray, t_calc_data data, t_game *game)
{
	t_position	is;

	is = find_is(simray, data);
	if ((data.side == 0 && data.stepx < 0))
	{
		game->door_coord_x = (int)simray.pos_x - 1;
		game->door_coord_y = (int)simray.pos_y;
		game->pixel = is.y - floor(is.y);
		if (is.y > (int)simray.pos_y && is.y < (int)simray.pos_y + 1)
			return (1);
	}
	if (data.side == 0 && data.stepx > 0)
	{
		game->door_coord_x = (int)simray.pos_x;
		game->door_coord_y = (int)simray.pos_y;
		game->pixel = is.y - floor(is.y);
		if (is.y > (int)simray.pos_y && is.y < (int)simray.pos_y + 1)
			return (1);
	}
	if (ray_hits_door_2(simray, data, game, is) == 1)
		return (1);
	return (0);
}

int	door_open(t_game *game)
{
	t_door	*tmp;

	if (game->map.full[game->door_coord_x][game->door_coord_y] == 'D')
	{
		tmp = game->doors;
		while (tmp != NULL)
		{
			if (tmp->x == game->door_coord_x && tmp->y == game->door_coord_y)
			{
				if (game->pixel < tmp->open)
				{
					game->door_offset = tmp->open;
					return (1);
				}
				else
					return (0);
			}
			tmp = tmp->next;
		}
		return (0);
	}
	return (0);
}

t_calc_data	calc_door(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;
	t_simray	simray;

	current_pos = calc_current_pos(game, ray, data);
	simray = calc_sim_ray(ray, current_pos);
	if (ray_hits_door(simray, data, game) == 1)
	{
		if (door_open(game) == 0)
		{
			return (data);
		}
		data.hit = 1;
		data.door_found = 1;
		if (data.side == 0)
			data.sidedistx += data.deltadistx / 2;
		else
			data.sidedisty += data.deltadisty / 2;
		return (data);
	}
	else
		return (data);
}
