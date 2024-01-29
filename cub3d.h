/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:17:26 by fstark            #+#    #+#             */
/*   Updated: 2024/01/29 12:58:14 by fstark           ###   ########.fr       */
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

# define PRESS_W			119
# define PRESS_Q			113
# define PRESS_S			115
# define PRESS_D			100
# define PRESS_A			97
# define PRESS_ESC			65307
# define PRESS_LEFT			65361
# define PRESS_RIGHT		65363

typedef struct s_data2
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data2;
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

/*typedef struct s_free
{
	int			malloc_map;
	int			malloc_display;
	int			malloc_window;
	int			malloc_sprites;
}	t_free;*/

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
	t_data2		west_data;
	t_image		east;
	t_data2		east_data;
	t_image		north;
	t_data2		north_data;
	t_image		south;
	t_data2		south_data;
	int			floor;
	int			ceiling;
}	t_images;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		num;
	double	distance;
	double	pixel;
	int		direction;
}	t_ray;

typedef struct s_calc_data
{
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		ray_map_x;
	int		ray_map_y;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}	t_calc_data;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			player_sprite;
	t_map		map;
	t_locations	locations;
	t_images	images;
	t_player	pl;
	t_data2		img;
	int			mouse_y;
	int			mouse_x;
	t_calc_data	first_ray;
	t_calc_data	last_ray;
	int			free_mouse;

}	t_game;

void	ft_check_input(int argc, char **argv, t_game *game);
void	ft_error_msg(char *message, t_game *game);
void	ft_read_map(t_game *game, char *argv);
char	*ft_strldup(char *s, size_t len);
int		find_sprites(t_game *game, char *str);
int		close_game(t_game *game);
void	raycasting(t_game *game);
void	ft_check_map(t_game *game);
int		manage_input(int keysym, t_game *game);
t_ray	calculate_distance_to_wall(t_game *game, t_ray ray);
int		my_mlx_pixel_get(t_data2 *data, int x, int y);
void	my_mlx_pixel_put(t_data2 *data, int x, int y, int color);
int		update_frame(t_game *game);
int		manage_mouse(int button, int x, int y, t_game *game);
void	draw_minimap(t_game *game);
int		convert_color(t_colour color);
void	init_images_colours(t_game *game);
void	ft_init_locations(t_game *game);
void	ft_init_mlx(t_game *game);
void	ft_init_win(t_game *game);
int		ft_atoi_image(char *nptr, int i);
int		add_colour(t_game *game, char *str, int i);
int		compare_to_identifier(char *str, int i);
void	draw_character_line_of_sight(t_game *game);
int		char_part_of_map(char c);
void	check_surrounded(t_game *game);

#endif