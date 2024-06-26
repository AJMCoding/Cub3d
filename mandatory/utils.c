/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:22:41 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:22:42 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				num;

	num = 0;
	result = 0;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (256);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i++] - '0');
		if (result > 255)
			return (256);
		num++;
		if (num > 3)
			return (256);
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

char	*ft_strldup_save(char *s, size_t len, t_game *game)
{
	char	*str;

	str = ft_strldup(s, len);
	if (str == NULL)
		ft_error_msg("Malloc error.", game);
	return (str);
}
