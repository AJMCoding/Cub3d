/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:14:26 by fstark            #+#    #+#             */
/*   Updated: 2024/03/20 15:14:37 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

# define WIN_HEIGHT			540
# define WIN_WIDTH			960

# define PI					3.14159265358979323846

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
	char		*sprite;
	char		*door;
	char		*a_sprite1;
	char		*a_sprite2;
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
	t_image		sprite;
	t_data2		sprite_data;
	t_image		door;
	t_data2		door_data;
	t_image		a_sprite1;
	t_data2		a_sprite1_data;
	t_image		a_sprite2;
	t_data2		a_sprite2_data;
	int			floor;
	int			ceiling;
}	t_images;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	true_dir_x;
	double	true_dir_y;
	int		map_x;
	int		map_y;
	int		num;
	double	distance;
	double	pixel;
	int		direction;
	int		door_found;
}	t_ray;

typedef struct s_simray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	false_dir_x;
	double	false_dir_y;
}	t_simray;

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
	int		door_found;
}	t_calc_data;

typedef struct s_door
{
	int				x;
	int				y;
	double			open;
	struct s_door	*next;
}	t_door;

typedef struct s_sprite
{
	int				x;
	int				y;
	int				printed;
	int				type;
	struct s_sprite	*next;
}	t_sprite;

typedef struct s_input
{
	int	front;
	int	back;
	int	left;
	int	right;
	int	turn_left;
	int	turn_right;
}	t_input;

typedef struct s_sprite_calc
{
	double	angle;
	double	distance;
	double	range;
	double	relative_angle;
	double	true_angle;
	double	starting_point;
}	t_sprite_calc;

typedef struct s_sprite_drawing
{
	double		height;
	double		width;
	double		x;
	double		y;
	int			i;
	int			j;
	int			color;
}	t_sprite_drawing;
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
	int			door_coord_x;
	int			door_coord_y;
	double		pixel;
	t_input		input;
	t_door		*doors;
	long long	frame;
	long long	frame_num;
	double		door_offset;
	t_sprite	*sprites;
	double		*distances;
	char		*str;
}	t_game;

void			ft_check_input(int argc, char **argv, t_game *game);
void			free_game_sprites(t_game *game);
void			ft_error_msg(char *message, t_game *game);
void			ft_read_map(t_game *game, char *argv);
char			*ft_strldup(char *s, size_t len);
int				find_sprites(t_game *game, char *str);
int				close_game(t_game *game);
void			raycasting(t_game *game);
void			ft_check_map(t_game *game);
int				manage_input(int keysym, t_game *game);
int				manage_input_release(int keysym, t_game *game);
t_ray			calculate_distance_to_wall(t_game *game, t_ray ray);
int				my_mlx_pixel_get(t_data2 *data, int x, int y);
void			my_mlx_pixel_put(t_data2 *data, int x, int y, int color);
int				update_frame(t_game *game);
int				manage_mouse(int button, int x, int y, t_game *game);
void			draw_minimap(t_game *game);
int				convert_color(t_colour color);
void			init_images_colours(t_game *game);
void			ft_init(t_game *game);
void			ft_init_mlx(t_game *game);
void			ft_init_win(t_game *game);
int				ft_atoi_image(char *nptr, int i);
int				add_colour(t_game *game, char *str, int i);
int				compare_to_identifier(char *str, int i);
void			draw_character_line_of_sight(t_game *game);
int				char_part_of_map(char c);
void			check_surrounded(t_game *game);
t_calc_data		calc_door(t_game *game, t_ray ray, t_calc_data data);
long long		millitimestamp(void);
int				manage_frames(t_game *game);
void			save_sprite(t_game *game, int x, int y, int num);
void			draw_sprites(t_game *game);
double			convert_angle(double angle, double range);
t_sprite_calc	calc_sprite(t_game *game, double x, double y);
int				list_size_sprites(t_sprite *sprites);
int				compare_range(t_sprite *tmp, t_sprite *tmp2, t_game *game);
char			*ft_strldup_save(char *s, size_t len, t_game *game);
void			change_player_pos(t_game *g, int direction);
void			change_player_pos_side(t_game *g, int direction);
void			rotate_camera(t_game *g, int direction, double i);
int				find_sprite_color(t_sprite *sprite, int x, int y, t_game *game);
void			free_allocated_memory(t_game *game);
t_simray		calc_sim_ray(t_ray ray, t_position current_pos);
t_position		find_is(t_simray simray, t_calc_data data);
t_calc_data		calculate_ray(t_game *game, t_ray ray, t_calc_data data);
void			draw_floor_ceiling(t_game *game, t_data2 img);
void			movements(t_game *game);
int				check_all_found(t_game *game);

#endif
