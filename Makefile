# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/31 21:35:21 by smaccary          #+#    #+#              #
#    Updated: 2020/07/31 21:35:21 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.exe


CC = x86_64-w64-mingw32-gcc.exe
CFLAGS = -Wall -Wextra -g3

MAKE = mingw32-make.exe

MLX_BASENAME = libmlx.a
MLX_DIR = ./minilibx_sdl2
MLX_LIB = $(MLX_DIR)/$(MLX_BASENAME)

SDL_DIR = $(MLX_DIR)/SDL

INCLUDES_DIR = ./includes
INCLUDES = -I$(INCLUDES_DIR) -I$(SDL_DIR)/include/SDL2
HEADERS = $(addprefix $(INCLUDES_DIR)/, main.h mlx.h)

SRC_DIR = ./srcs
SRC = $(addprefix $(DIRSRC)/, main.c)

OBJDIR = obj
OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)
OBJ_PATHS = $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')


LINKS = -L"$(MLX_DIR)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer \
-lSDL2_ttf  -lmingw32 -lSDL2main -luser32 -lgdi32 -lwinmm -ldxguid


all: $(NAME) $(HEADERS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME) $(LINKS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(MLX_LIB)
	@mkdir -p $(OBJ_PATHS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(MLX_DIR)


re: fclean all	

.PHONY: clean fclean