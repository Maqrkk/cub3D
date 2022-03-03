# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mpeerdem <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/17 09:09:50 by mpeerdem      #+#    #+#                  #
#    Updated: 2020/03/06 16:24:00 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D
CC =			gcc
CFLAGS =		-Wall -Werror -Wextra
FRAMEWORKS =	-framework OpenGL -framework AppKit
MLX =			mlx
MLXLIB =		libmlx.dylib
LIBFT =			libft.a
SDIR =			srcs
ODIR =			objs
INC =			includes
_OBJS =			map_parser1 map_parser3 \
				utilities1 utilities2 report_error \
				map_functions struct_functions \
				draw_functions1 sprite_functions \
				move_player object_functions \
				ivector_functions dvector_functions \
				raycaster1 raycaster2 close_game \
				bitmap_functions
OBJS =			$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
_NORMAL =		cub3d draw_functions2 hook_functions texture_functions \
				map_parser2 validate_map
NORMAL =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_NORMAL)))
BONUS =			$(addsuffix _bonus.o, $(addprefix $(ODIR)/, $(_NORMAL)))
_EXTRA =		draw_functions3
EXTRA =			$(addsuffix _bonus.o, $(addprefix $(ODIR)/, $(_EXTRA)))

ifdef WITH_BONUS
	HEADER =	cub3d_bonus.h
	ALL_OBJS =	$(OBJS) $(BONUS) $(EXTRA)
	OTHER =		$(NORMAL)
else
	HEADER =	cub3d.h
	ALL_OBJS =	$(OBJS) $(NORMAL)
	OTHER =		$(BONUS)
endif

all: $(NAME)

.PHONY: all clean fclean re

$(NAME): $(ALL_OBJS) $(MLXLIB) $(LIBFT)
	rm -f $(OTHER)
	$(CC) -L. -lmlx -lft $(FRAMEWORKS) -o $(NAME) $(ALL_OBJS)

$(MLXLIB):
	cd $(MLX) && make
	mv $(MLX)/$(MLXLIB) .

$(LIBFT):
	cd libft && make
	mv libft/$(LIBFT) .

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -I$(MLX) -Ilibft -I$(INC) -c $< -o $@

bonus:
	@make WITH_BONUS=1

clean:
	cd $(MLX) && make clean
	cd libft && make clean
	rm -f $(OBJS)
	rm -f $(NORMAL)
	rm -f $(BONUS)
	rm -f $(EXTRA)

fclean: clean
	rm -f $(NAME)
	rm -f $(MLXLIB)
	rm -f $(LIBFT)

re: fclean all
