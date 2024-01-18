#include "cub3d.h"


t_ray	calculate_ray_angle(t_game *game, int rays)
{
	t_ray	ray;


	//ray.dir_x = game->pl.dir.x + rays * 0.66 / (double)WIN_WIDTH;
	//printf("ray_dir.dir_x: %f at pos: %d\n", ray.dir_x, rays);
	
	//int angle = rays * 0.66 / (double)WIN_WIDTH ;
	double cameraX = 2 * rays / (double)WIN_WIDTH - 1; //x-coordinate in camera space
	ray.dir_x = game->pl.dir.x + game->pl.plane.x * cameraX;
	ray.dir_y = game->pl.dir.y + game->pl.plane.y * cameraX;
	//printf("ray_dir.dir_x: %f y: %f at pos: %d\n", ray.dir_x, ray.dir_y, rays);
	ray.map_x = (int)game->pl.pos.x;
    ray.map_y = (int)game->pl.pos.y;
	ray.num = rays;
	return (ray);
}

t_ray	calculate_distance_to_wall(t_game *game, t_ray ray)
{
	double sideDistX;
	double sideDistY;

	//double deltaDistX = (ray.dir_x == 0) ? 1e30 : abs(1 / (int)ray.dir_x);
    //double deltaDistY = (ray.dir_y == 0) ? 1e30 : abs(1 / (int)ray.dir_y);

	double deltaDistX;
	double deltaDistY;
	//deltaDistX = sqrt(1 + (ray.dir_y * ray.dir_y) / (ray.dir_x * ray.dir_x));
	//deltaDistY = sqrt(1 + (ray.dir_x * ray.dir_x) / (ray.dir_y * ray.dir_y));
	//printf("deltaDistX: %f deltaDistY: %f\n", deltaDistX, deltaDistY);
	if (ray.dir_x == 0.0) 
	{
    	deltaDistX = 1e30;
	} 
	else 
	{
		deltaDistX = fabs(1.0 / ray.dir_x);
	}
	if (ray.dir_y == 0.0) 
	{
		deltaDistY = 1e30;
	} 
	else 
	{
    	deltaDistY = fabs(1.0 / ray.dir_y);
	}
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
		//sideDistY = (ray.map_y + 1.0 - game->pl.pos.y) * deltaDistY;
    }
	else
    {
		stepY = 1;
    	sideDistY = (ray.map_y + 1.0 - game->pl.pos.y) * deltaDistY;
		//sideDistY = (game->pl.pos.y - ray.map_y) * deltaDistY;
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
        //Check if ray has hit a wall
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
	printf("ray.direction: %d\n dir: x: %f y: %f\n", ray.direction, ray.dir_x, ray.dir_y);
	//printf("wallX: %f\n", wallX);

	//printf("found map wall at: %d, %d value: %c distance: %f \n", ray.map_x, ray.map_y, game->map.full[ray.map_x][ray.map_y], perpWallDist);
	//if (ray.num == 959)
		//printf("found map wall at: %d, %d value: %c distance: %f \n", ray.map_x, ray.map_y, game->map.full[ray.map_x][ray.map_y], perpWallDist);
	return (ray);
}

void	my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
/*
void	draw_wall(int rays, double distance, t_data2 img)
{
	double height;
	int start;
	int end;

	height = (WIN_HEIGHT / (distance + 1));
	start = (WIN_HEIGHT - height) / 2;
	end = (WIN_HEIGHT + height) / 2;
	//printf("ray: %d start: %d end: %d\n", rays, start, end);
	while (start < end)
	{
		my_mlx_pixel_put(&img, rays, start, 0x00FF00);
		start++;
	}
}*/

void	draw_wall(int rays, t_ray ray, t_data2 img)
{
	int height;
	int start;
	int end;

	height = (int)((WIN_HEIGHT / ray.distance) * 0.8);
	start = -height / 2 + WIN_HEIGHT / 2;
	if(start < 0) 
		start = 0;
	end = height / 2 + WIN_HEIGHT / 2;
	if(end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	//printf("ray: %d start: %d end: %d\n", rays, start, end);
	while (start < end)
	{
		my_mlx_pixel_put(&img, rays, start, 0x00FF00);
		start++;
	}
}

void	draw_floor_ceiling(t_game *game, t_data2 img)
{
	int x;
	int y;

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

void	raycasting(t_game *game)
{
	int rays;
	t_ray ray;
	t_data2	img;

	rays = 0;
	img.img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_floor_ceiling(game, img);
	while (rays < WIN_WIDTH)
	{
		//calculate ray angle
		ray = calculate_ray_angle(game, rays);
		//calculate distance to wall
		ray = calculate_distance_to_wall(game, ray);
		//draw the wall
		draw_wall(rays, ray, img);
		rays ++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img.img, 0, 0);
}