/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:20:27 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:20:30 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	int				n;

	n = 0;
	result = 0;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (256);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i++] - '0');
		if (result > 255)
			return (256);
		n++;
		if (n > 3)
			return (256);
	}
	return (result);
}

int	char_part_of_map(char c)
{
	if (c == '0' || c == '1' || c == 'D' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == ' ' || c == 'P' || c == 'A')
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

/* char	*ft_strldup_save(char *s, size_t len, t_game *game)
{
	char	*str;

	str = ft_strldup(s, len);
	if (str == NULL)
		ft_error_msg("Malloc error.", game);
	return (str);
} */

long long	millitimestamp(void)
{
	struct timeval	timeval;
	long long		microtime;

	gettimeofday(&timeval, NULL);
	microtime = timeval.tv_sec * 1000LL + timeval.tv_usec / 1000;
	return (microtime);
}
