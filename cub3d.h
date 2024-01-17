/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:17:26 by fstark            #+#    #+#             */
/*   Updated: 2024/01/17 16:42:03 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>


# define WIN_HEIGHT			540
# define WIN_WIDTH			960
/*
# define WALL				'1'
# define FLOOR 				'0'
# define COIN	  			'C'
# define PLAYER				'P'
# define EXIT 		 		'E'
# define FILLER				'N'

# define WALL_XPM			"textures/wall.xpm"
# define FLOOR_XPM			"textures/floor.xpm"
# define COINS_XPM			"textures/coin-bag.xpm"
# define PLAYER_XPM			"textures/player.xpm"
# define EXIT_XPM			"textures/exit.xpm"

# define PRESS_W			119
# define PRESS_S			115*/
# define PRESS_D			100
# define PRESS_A			97
# define PRESS_ESC			65307

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_player
{
	t_position	pos;
	t_position	dir;
	t_position	plane;
}	t_player;
typedef struct s_map
{
	char		**full;
}	t_map;

typedef struct s_free
{
	int			malloc_map;
	int			malloc_display;
	int			malloc_window;
	int			malloc_sprites;
}	t_free;

typedef struct s_image
{
	void	*xpm_ptr;
	int		width;
	int		height;
}	t_image;

typedef struct s_colour
{
	int		red;
	int		green;
	int		blue;
}	t_colour;

typedef struct s_locations
{
	char		*west;
	char		*east;
	char		*north;
	char		*south;
	t_colour	floor;
	t_colour	ceiling;
}	t_locations;

typedef struct s_images
{
	t_image		west;
	t_image		east;
	t_image		north;
	t_image		south;
	t_colour	floor;
	t_colour	ceiling;
}	t_images;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			player_sprite;
	t_map		map;
	t_locations	locations;
	t_images	images;
	t_free		free;
	t_player	pl;
}	t_game;

typedef struct s_ray
{
	double dir_x;
	double dir_y;
	int map_x;
	int map_y;
}	t_ray;

typedef struct	s_data2 {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data2;

void	ft_check_input(int argc, char **argv, t_game *game);
int		ft_error_msg(char *message, t_game *game);
void	ft_read_map(t_game *game, char *argv);
char	*ft_strldup(char *s, size_t len);
int		find_sprites(t_game *game, char *str);
void	ft_find_images(t_game *game);
int	close_game(t_game *game);
void	raycasting(t_game *game);

#endif