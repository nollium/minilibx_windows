NAME = test.exe


CC = x86_64-w64-mingw32-gcc.exe
CFLAGS = -Wall -Wextra -g3

MAKE = mingw32-make.exe

INCLUDES_DIR = ./includes
INCLUDES = -I$(INCLUDES_DIR)
HEADERS = $(addprefix $(INCLUDES_DIR)/, main.h mlx.h)

SRC_DIR = ./srcs
SRC = $(addprefix $(DIRSRC)/, main.c)

OBJDIR = obj
OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)
OBJ_PATHS = $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

MLX_BASENAME = libmlx.a
MLX_DIR = ./minilibx_sdl2
MLX_LIB = $(MLX_DIR)/$(MLX_BASENAME)

LINKS = -L"$(MLX_DIR)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer \
-lSDL2_ttf  -lmingw32 -lSDL2main $(MLX_DIR)/SDL2.dll -luser32 -lgdi32 -lwinmm -ldxguid


all: $(NAME) $(HEADERS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -Wl,-rpath=$(MLX_DIR)/. $(INCLUDES) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME) $(LINKS)

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