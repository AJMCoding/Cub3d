#include "cub3d.h"

int	convert_color(t_colour color)
{
	int	rgb;

	rgb = color.red;
	rgb = (rgb << 8) + color.green;
	rgb = (rgb << 8) + color.blue;
	return (rgb);
}

int	ft_atoi_image(char *nptr, int i)
{
	long long int	result;

	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > 255)
			return (256);
		result = result * 10 + (nptr[i++] - '0');
	}
	return (result);
}