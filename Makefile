
NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g #-fsanitize=address,leak,undefined
FLAGS			=	-lreadline
MINILIBX_FLAGS	=	-lmlx -lXext -lX11 -lm

SRCS            =	main.c ft_check_input.c ft_close_game.c ft_read_map.c \
					ft_find_sprites.c raycasting.c ft_manage_input.c ft_check_map.c \
					raycasting_utils.c raycasting_calc.c init.c utils.c \
					ft_find_sprites2.c ft_check_map_surrounded.c\

SRCS_BONUS      =	main.c ft_check_input.c ft_close_game.c ft_read_map.c \
					ft_find_sprites.c raycasting.c ft_manage_input.c ft_check_map.c \
					raycasting_utils.c raycasting_calc.c minimap.c init.c utils.c \
					ft_find_sprites2.c minimap_player.c ft_check_map_surrounded.c\

SRCS_DIR			=	mandatory
SRCS_DIR_BONUS		=	bonus

OBJ_DIR				=	obj
OBJ_DIR_BONUS		=	obj_bonus
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS			=	$(SRCS_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)

LIBFT_PATH			= 	./libft
LIBFT				= 	$(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o:		$(SRCS_DIR)/%.c	
								$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o:		$(SRCS_DIR_BONUS)/%.c	
								$(CC) $(CFLAGS) -c $< -o $@

all:			    $(NAME)

$(LIBFT):		
						make -C $(LIBFT_PATH) all

$(NAME): 		    $(LIBFT) $(OBJ_DIR) $(OBJS)
						cp	$(LIBFT) $(NAME)
				        $(CC) $(CFLAGS) $(MINILIBX_FLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft -lreadline

$(OBJ_DIR):		
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):		
					mkdir -p $(OBJ_DIR_BONUS)

bonus:				$(LIBFT) $(OBJ_DIR_BONUS) $(OBJS_BONUS)
						cp	$(LIBFT) $(NAME_BONUS)
				        $(CC) $(CFLAGS) $(MINILIBX_FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) -L$(LIBFT_PATH) -lft -lreadline

clean:
						make -C $(LIBFT_PATH) clean
					    $(RM) $(OBJ_DIR)
						$(RM) $(OBJ_DIR_BONUS)

fclean: 		    clean
						make -C $(LIBFT_PATH) fclean
				        $(RM) $(NAME)
						$(RM) $(NAME_BONUS)

re: 			fclean all

run:			${NAME}
				${VALGRIND} ./${NAME} map.ber

.PHONY: 		all clean fclean re run libft
