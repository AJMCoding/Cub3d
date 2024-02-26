#include "cub3d_bonus.h"
#include <X11/X.h>

/*int find_direction(t_ray ray, t_calc_data data)
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
		//ray.map_x += data.stepx;
		data.side = 0;
	}
	else
	{
		data.sidedisty += data.deltadisty;
		//ray.map_y += data.stepy;
		data.side = 1;
	}
	if (data.side == 0)
		ray.distance = (data.sidedistx - data.deltadistx);
	else
		ray.distance = (data.sidedisty - data.deltadisty);
	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 0)
		next_hit_pos.x = ray.pixel + ray.map_x;
	else
		next_hit_pos.y = ray.pixel + ray.map_y;
	if (data.side == 1)
		next_hit_pos.x = ray.map_x;
	else
		next_hit_pos.y = ray.map_y;
	return (next_hit_pos);
}

t_position	calc_current_pos(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;

	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 0)
		current_pos.x = ray.pixel + ray.map_x;
	else
		current_pos.y = ray.pixel + ray.map_y;
	if (data.side == 0)
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
	t_position	next_pos;
	t_position	current_pos;
	//double		p;

	t_calc_data	data2;
	data2 = data;
	//find if we first hit the middle of the square or the side of the square
	next_pos = calc_next_hit_pos(game, ray, data);
	current_pos = calc_current_pos(game, ray, data);
	if (ray.num == 0)
	{
		printf("next_hit_pos: %f %f\n", next_pos.x, next_pos.y);
		printf("current_pos: %f %f\n", current_pos.x, current_pos.y);
	}
	//printf("i: %d\n", i);
	if (current_pos.x > next_pos.x && current_pos.y > next_pos.y)
	{
		//printf("2\n");
		if (current_pos.x < next_pos.x - 0.5)
		{
			if (ray.num == 0)
				printf("0\n");
			return (data2);
		}
		else
		{
			//p = calculate_pos_hits_middle_of_square(next_pos, current_pos, data);
			data.ray_map_x = current_pos.x - 0.5;
			//data.ray_map_y = current_pos.y - p;
			data.sidedisty += data.deltadisty / 2;
		}

	}
	else if (current_pos.x < next_pos.x && current_pos.y < next_pos.y)
	{
		//printf("3\n");
		if (current_pos.x < next_pos.x + 0.5)
		{
			if (ray.num == 0)
				printf("0\n");
			return (data2);
		}
		else
		{
			//p = calculate_pos_hits_middle_of_square(next_pos, current_pos, data);
			data.ray_map_x = current_pos.x + 0.5;
			//data.ray_map_y = current_pos.y + p;
			data.sidedisty -= data.deltadisty / 2;
		}

	}
	else if (current_pos.x > next_pos.x && current_pos.y < next_pos.y)//correct
	{
		//printf("4\n");
		if (current_pos.y > next_pos.y - 0.5)
		{
			if (ray.num == 0)
				printf("0\n");
			return (data2);
		}
		else
		{
			//p = calculate_pos_hits_middle_of_square(next_pos, current_pos, data);
			//data.ray_map_x = current_pos.x - p;
			//data.ray_map_y = current_pos.y + 0.5;
			data.sidedistx += data.deltadistx / 2;
		}

	}
	else if (current_pos.x < next_pos.x && current_pos.y > next_pos.y)
	{
		//printf("5\n");
		if (current_pos.y < next_pos.y + 0.5)
		{
			if (ray.num == 0)
				printf("0\n");
			return (data2);
		}
		else
		{
			//p = calculate_pos_hits_middle_of_square(next_pos, current_pos, data);
			//data.ray_map_x = current_pos.x + p;
			//data.ray_map_y = current_pos.y - 0.5;
			data.sidedistx -= data.deltadistx / 2;
		}

	}
	data.hit = 1;
	data.door_found = 1;
	if (ray.num == 0)
		printf("1\n");
	return (data);
	
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
	
}*/

/* t_position	calc_next_hit_pos(t_game *game, t_ray ray, t_calc_data data)
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
	data.ray_map_x = ray.map_x;
	data.ray_map_y = ray.map_y;
	ray.map_x = data.ray_map_x;
	ray.map_y = data.ray_map_y;
	if (data.side == 0)
		ray.distance = (data.sidedistx - data.deltadistx);
	else
		ray.distance = (data.sidedisty - data.deltadisty);
	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 1)
		next_hit_pos.x = (data.stepx * ray.pixel) + ray.map_x;
	else
		next_hit_pos.y = (data.stepy * ray.pixel) + ray.map_y;
	if (data.side == 0)
		next_hit_pos.x = ray.map_x;
	else
		next_hit_pos.y = ray.map_y;
	return (next_hit_pos);
} */

t_position	calc_current_pos(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;

	data.ray_map_x = ray.map_x;
	data.ray_map_y = ray.map_y;
	ray.map_x = data.ray_map_x;
	ray.map_y = data.ray_map_y;
	if (data.side == 0)
		ray.distance = (data.sidedistx - data.deltadistx);
	else
		ray.distance = (data.sidedisty - data.deltadisty);
	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	if (data.side == 1)
		current_pos.x = ray.pixel + ray.map_x;
	else
		current_pos.y = ray.pixel + ray.map_y;
	if (data.side == 0)
		current_pos.x = ray.map_x;
	else
		current_pos.y = ray.map_y;
	return (current_pos);
}

/* double	calculate_pos_hits_middle_of_square(t_position start_pos, t_position end_pos, t_calc_data data)
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
} */

int door_is_open(t_position intersection, t_game *game)
{
/* 	if (game->map.full[(int)intersection.x][(int)intersection.y] == 3)
	{
		//find door opened status and compare
		return (1);
	} */
	(void)intersection;
	(void)game;
	return (1);
}

t_position findIntersectionX(t_simray simray, double y, t_calc_data data) 
{
	t_position	intersection;
	(void)data;

	if (simray.false_dir_y != 0) 
	{
		intersection.y = y;
		/* if (data.stepy < 0)
			intersection.x = simray.pos_x + (0.5 * fabs(simray.dir_y));
		else
		 	intersection.x = simray.pos_x - (0.5 * fabs(simray.dir_y)); */
		intersection.x = simray.pos_x - (0.5 * simray.dir_y);
	}
	else 
	{
		intersection.x = NAN;
		intersection.y = NAN;  // Non-intersecting or coincident with x-axis
	}
	return (intersection);
}

t_position findIntersectionY(t_simray simray, double x, t_calc_data data) 
{
	t_position	intersection;
	(void)data;

    if (simray.false_dir_x != 0)
	{
        intersection.x = x;
/* 		if (data.stepx < 0)
       		intersection.y = simray.pos_y + (0.5 * fabs(simray.dir_x));
		else
			intersection.y = simray.pos_y - (0.5 * fabs(simray.dir_x)); */
		intersection.y = simray.pos_y - (0.5 * simray.dir_x);
    }
	else
	{
        intersection.x = NAN;
		intersection.y = NAN;  // Non-intersecting or coincident with y-axis
    }
	return (intersection);
}

t_position	find_intersection(t_simray simray, double x, double y, t_calc_data data)
{
	t_position	intersection;
	//find intersection with door
	if (data.side == 1)
	{
		intersection = findIntersectionX(simray, y, data);
	}
	else
	{
		intersection = findIntersectionY(simray, x, data);
	}
	return (intersection);
}

t_simray	calc_sim_ray(t_ray ray, t_position current_pos)
{
	t_simray	simray;

	simray.dir_x = ray.true_dir_x;
	simray.dir_y = ray.true_dir_y;
	simray.false_dir_x = ray.dir_x;
	simray.false_dir_y = ray.dir_y;
	simray.pos_x = current_pos.x;
	simray.pos_y = current_pos.y;
	return (simray);
}

int	ray_hits_door(t_simray	simray, t_calc_data data, t_game *game, int i)
{

	t_position	intersection;
	(void)game;

	if (data.side == 0) //x
	{
		//printf("side == 0\n");
		if (data.stepx < 0)
		{
			intersection = find_intersection(simray, simray.pos_x + 0.5, simray.pos_y, data);
			//printf("1: side == 0, step_y < 0\n");
		}
		else
		{
		 	intersection = find_intersection(simray, simray.pos_x - 0.5, simray.pos_y, data);
			//printf("2: side == 0, step_y > 0\n");
		}
	}
	else //y
	{
		//printf("side == 1\n");
		if (data.stepy < 0)
		{
			intersection = find_intersection(simray, simray.pos_x, simray.pos_y + 0.5, data);
			//printf("3: side == 1, step_x < 0\n");
		}
		else
		{
			intersection = find_intersection(simray, simray.pos_x, simray.pos_y - 0.5, data);
			//printf("4: side == 1, step_x < 0\n");
		}
	}
	if (i == 0)
	{
		printf("inter x:%f inter y:%f\n", intersection.x, intersection.y);
		printf("dir x:%f dir y:%f\n", simray.dir_x, simray.dir_y);
	}
/* 	if (data.side == 0)
	{
		if (data.stepy < 0)
		{
			if (i == 0)
				printf(" inter.x:%f simray.x:%f\n", intersection.x, simray.pos_x + 1);
			if (intersection.x > (int)simray.pos_x && intersection.x < (int)simray.pos_x + 1)
				return (1);
			else
			 	return (0);
		}
		else 
		{
			if (intersection.x > (int)simray.pos_x && intersection.x < (int)simray.pos_x - 1)
				return (1);
			else
			 	return (0);	

		}
	}
	else 
	{
		if (data.stepy < 0)
		{
			if (intersection.y > simray.pos_y && intersection.y < simray.pos_y + 1)
				return (1);
			else
			 	return (0);
		}
		else 
		{
			if (intersection.y > simray.pos_y && intersection.y < simray.pos_y - 1)
				return (1);
			else
			 	return (0);	

		}
	}*/
	if ((data.side == 0 && data.stepx < 0))
	{
		if (intersection.x > (int)simray.pos_x && intersection.x < (int)simray.pos_x + 1)
			return (1);
	}
	if (data.side == 1 && data.stepx > 0)
	{
		if (intersection.x > (int)simray.pos_x - 1 && intersection.x < (int)simray.pos_x)
			return (1);
	}
	if (data.side == 0 && data.stepy < 0)
	{
		if (intersection.y > (int)simray.pos_y && intersection.y < (int)simray.pos_y + 1)
			return (1);
	}
	if (data.side == 1 && data.stepy > 0)
	{
		if (intersection.y > (int)simray.pos_y - 1 && intersection.y < (int)simray.pos_y)
			return (1);
	}
	return (0);
}

t_calc_data	calc_door(t_game *game, t_ray ray, t_calc_data data)
{
	t_position	current_pos;
	t_simray	simray;

	current_pos = calc_current_pos(game, ray, data);
	simray = calc_sim_ray(ray, current_pos);
/* 	if (ray.num == 0)
	{
		printf("current x:%f\n", current_pos.x);
		printf("current y:%f\n", current_pos.y);
	} */
	if (ray_hits_door(simray, data, game, ray.num) == 1)
	{
		//data.hit = 1;
		//data.door_found = 1;
		return (data);
	}
	else
		return (data);
}
