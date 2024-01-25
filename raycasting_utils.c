#include "cub3d.h"

void	my_mlx_pixel_put(t_data2 *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_mlx_pixel_get(t_data2 *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + ((y)* (data->bits_per_pixel / 8) + (x * 64) * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	//printf("color: %d\n at pos x:%d y:%d, adress: %d\n", color, x, y, (y + (x * 64)));
	return (color);
}
