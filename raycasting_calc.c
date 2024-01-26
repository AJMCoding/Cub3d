#include "cub3d.h"

//1 = north 2 = east 3 = south 4 = west
int	set_ray_direction(t_ray ray, t_calc_data data)
{
	if (data.side == 0)
	{
		if (ray.dir_x < 0)
			return (1);
		else
			return (3);
	}
	else
	{
		if (ray.dir_y < 0)
			return (2);
		else
			return (4);
	}
}

t_calc_data	calculate_ray2(t_game *game, t_ray ray, t_calc_data data)
{
	if (ray.dir_x < 0)
	{
		data.stepX = -1;
		data.sideDistX = (game->pl.pos.x - ray.map_x) * data.deltaDistX;
	}
	else
	{
		data.stepX = 1;
		data.sideDistX = (ray.map_x + 1.0 - game->pl.pos.x) * data.deltaDistX;
	}
	if (ray.dir_y < 0)
	{
		data.stepY = -1;
		data.sideDistY = (game->pl.pos.y - ray.map_y) * data.deltaDistY;
	}
	else
	{
		data.stepY = 1;
		data.sideDistY = (ray.map_y + 1.0 - game->pl.pos.y) * data.deltaDistY;
	}
	return (data);
}

t_calc_data	calculate_ray(t_game *game, t_ray ray, t_calc_data data)
{
	data = calculate_ray2(game, ray, data);
	while (data.hit == 0)
	{
		if (data.sideDistX < data.sideDistY)
		{
			data.sideDistX += data.deltaDistX;
			ray.map_x += data.stepX;
			data.side = 0;
		}
		else
		{
			data.sideDistY += data.deltaDistY;
			ray.map_y += data.stepY;
			data.side = 1;
		}
		if (game->map.full[ray.map_x][ray.map_y] != '0' && game->map.full[ray.map_x][ray.map_y] != 'W' && game->map.full[ray.map_x][ray.map_y] != 'E' && game->map.full[ray.map_x][ray.map_y] != 'N' && game->map.full[ray.map_x][ray.map_y] != 'S')
			data.hit = 1;
	}
	data.ray_map_x = ray.map_x;
	data.ray_map_y = ray.map_y;
	if (ray.num == 0)
		game->first_ray = data;
	if (ray.num == WIN_WIDTH - 1)
		game->last_ray = data;
	return (data);
}

t_ray	calculate_distance_to_wall(t_game *game, t_ray ray)
{
	t_calc_data	data;

	data.hit = 0;
	if (ray.dir_x == 0.0)
		data.deltaDistX = 1e30;
	else
		data.deltaDistX = fabs(1.0 / ray.dir_x);
	if (ray.dir_y == 0.0)
		data.deltaDistY = 1e30;
	else
		data.deltaDistY = fabs(1.0 / ray.dir_y);
	data = calculate_ray(game, ray, data);
	ray.map_x = data.ray_map_x;
	ray.map_y = data.ray_map_y;
	if (data.side == 0)
		ray.distance = (data.sideDistX - data.deltaDistX);
	else
		ray.distance = (data.sideDistY - data.deltaDistY);
	if (data.side == 0)
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	ray.direction = set_ray_direction(ray, data);
	return (ray);
}

/*
t_ray	calculate_distance_to_wall(t_game *game, t_ray ray)
{
	double sideDistX;
	double sideDistY;
	
	double deltaDistX;
	double deltaDistY;
	if (ray.dir_x == 0.0) 
    	deltaDistX = 1e30;
	else 
		deltaDistX = fabs(1.0 / ray.dir_x);
	if (ray.dir_y == 0.0) 
		deltaDistY = 1e30;
	else 
    	deltaDistY = fabs(1.0 / ray.dir_y);
	
	//printf("deltaDistX: %f deltaDistY: %f\n", deltaDistX, deltaDistY);
	//calculate step and initial sideDist
	int stepX;
    int stepY;

	int hit = 0; //was there a wall hit?
    int side;

	if(ray.dir_x < 0)
      {
        stepX = -1;
        sideDistX = (game->pl.pos.x - ray.map_x) * deltaDistX;
      }
	else
      {
        stepX = 1;
        sideDistX = (ray.map_x + 1.0 - game->pl.pos.x) * deltaDistX;
      }
	if(ray.dir_y < 0)
    {
		stepY = -1;
		sideDistY = (game->pl.pos.y - ray.map_y) * deltaDistY;
    }
	else
    {
		stepY = 1;
    	sideDistY = (ray.map_y + 1.0 - game->pl.pos.y) * deltaDistY;
    }
	while(hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          ray.map_x += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          ray.map_y += stepY;
          side = 1;
        }
        if(game->map.full[ray.map_x][ray.map_y] != '0') 
			hit = 1;
	}
	//find distance
	if(side == 0) 
		ray.distance = (sideDistX - deltaDistX);
    else          
		ray.distance = (sideDistY - deltaDistY);
	//find position of wall, that was hit
	if (side == 0) // north or south
		ray.pixel = game->pl.pos.y + ray.distance * ray.dir_y;
	else           
		ray.pixel = game->pl.pos.x + ray.distance * ray.dir_x;
	ray.pixel -= floor((ray.pixel));
	//find which side of the wall was hit
	if (side == 0) // north or south
	{
		if (ray.dir_x < 0)
			ray.direction = 1;//north
		else
			ray.direction = 3;//south
	}
	else
	{
		if (ray.dir_y < 0)
			ray.direction = 2;//east
		else
			ray.direction = 4;//west
	}
	//ray.direction = side;
	//printf("ray.direction: %d\n dir: x: %f y: %f\n", ray.direction, ray.dir_x, ray.dir_y);
	//printf("wallX: %f\n", wallX);

	//printf("found map wall at: %d, %d value: %c distance: %f \n", ray.map_x, ray.map_y, game->map.full[ray.map_x][ray.map_y], perpWallDist);
	//if (ray.num == 959)
		//printf("found map wall at: %d, %d value: %c distance: %f \n", ray.map_x, ray.map_y, game->map.full[ray.map_x][ray.map_y], perpWallDist);
	return (ray);
}*/
