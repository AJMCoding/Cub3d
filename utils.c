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

int	char_part_of_map(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == ' ')
		return (1);
	return (0);
}

char	*ft_strldup(char *s, size_t len)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub_str = (char *)malloc(len + 1);
	if (sub_str == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		sub_str[i] = s[i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
