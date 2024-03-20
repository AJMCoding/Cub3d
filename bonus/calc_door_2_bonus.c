#include "cub3d_bonus.h"

t_position	find_intersection_x(t_simray simray, double y, t_calc_data data)
{
	t_position	intersection;

	intersection.y = y;
	if (data.stepy < 0)
		intersection.x = simray.pos_x - 0.5 * simray.dir_y;
	else
		intersection.x = simray.pos_x + 0.5 * simray.dir_y;
	return (intersection);
}

t_position	find_intersection_y(t_simray simray, double x, t_calc_data data)
{
	t_position	intersection;

	intersection.x = x;
	if (data.stepx < 0)
		intersection.y = simray.pos_y - (0.5 * simray.dir_x);
	else
		intersection.y = simray.pos_y + (0.5 * simray.dir_x);
	return (intersection);
}

t_position	find_is_2(t_simray simray,
								double x, double y, t_calc_data data)
{
	t_position	intersection;

	if (data.side == 1)
		intersection = find_intersection_x(simray, y, data);
	else
		intersection = find_intersection_y(simray, x, data);
	return (intersection);
}

t_position	find_is(t_simray simray, t_calc_data data)
{
	t_position	is;

	if (data.side == 0)
	{
		if (data.stepx < 0)
			is = find_is_2(simray, simray.pos_x + 0.5, simray.pos_y, data);
		else
			is = find_is_2(simray, simray.pos_x - 0.5, simray.pos_y, data);
	}
	else
	{
		if (data.stepy < 0)
			is = find_is_2(simray, simray.pos_x, simray.pos_y - 0.5, data);
		else
			is = find_is_2(simray, simray.pos_x, simray.pos_y + 0.5, data);
	}
	return (is);
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
