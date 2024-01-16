/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:17:26 by fstark            #+#    #+#             */
/*   Updated: 2024/01/16 11:06:07 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf/printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define IMG_HEIGHT			32
# define IMG_WIDTH			32

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
# define PRESS_S			115
# define PRESS_D			100
# define PRESS_A			97
# define PRESS_ESC			65307

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			columns;
	int			players;
	int			coins;
	int			exit;
	t_position	player;
	t_position	exit_pos;
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
	int		x;
	int		y;
}	t_image;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			movements;
	int			fastest;
	int			player_sprite;
	t_map		map;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		exit;
	t_image		player;
	t_free		free;
	int			calculated_shortest_path;

}	t_game;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *str, char c);
void	ft_read_map(t_game *game, char *argv);
t_image	ft_new_sprite(void *mlx, char *path, t_game *game);
void	ft_init_sprites(t_game *game);
void	ft_init_mlx(t_game *game);
void	ft_init_vars(t_game *game);
int		ft_error_msg(char *message, t_game *game);
int		ft_render_map(t_game *game);
size_t	ft_strlen(char *s);
void	ft_check_command_line_arguments(int argc, char **argv, t_game *game);
void	ft_verify_map(t_game *game);
int		manage_inputs(int keysym, t_game *game);
int		close_game(t_game *game);
void	victory(t_game *game);
void	verify_valid_path(t_game *game);
int		check_min_moves(t_game *game, int x, int y);
char	*ft_strdup(const char *s);
void	ft_init_free(t_game *game);
char	*ft_strchr(char *s, int c);
char	**create_array(t_game *game);

#endif