NAME = libmlx.a


CC = x86_64-w64-mingw32-gcc.exe
CFLAGS = -Wall -Wextra -g3


MAKE = mingw32-make.exe

SDL_DIR = ./SDL
SDL_INCLUDE_DIR = $(SDL_DIR)/include/SDL2

INCLUDES_DIR = ./includes
INCLUDES = -I$(INCLUDES_DIR) -I$(SDL_INCLUDE_DIR)
HEADERS = $(addprefix $(INCLUDES_DIR)/, mlx_int.h)

SRC_DIR = ./srcs
SRC = $(addprefix $(DIRSRC)/, mlx.c)

OBJDIR = obj
OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)
OBJ_PATHS = $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

LINKS = -L"$(SDL_DIR)/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer \
-lSDL2_ttf  -lmingw32 -lSDL2main -lSDL2.dll -luser32 -lgdi32 -lwinmm -ldxguid \
"$(SDL_DIR)/lib/libSDL2.a" "$(SDL_DIR)/lib/libSDL2.dll.a" \
"$(SDL_DIR)/lib/libSDL2_image.a" "$(SDL_DIR)/lib/libSDL2_image.dll.a" \
"$(SDL_DIR)/lib/libSDL2_mixer.a" "$(SDL_DIR)/lib/libSDL2_mixer.dll.a" \
"$(SDL_DIR)/lib/libSDL2_test.a" "$(SDL_DIR)/lib/libSDL2_ttf.a" \
"$(SDL_DIR)/lib/libSDL2_ttf.dll.a"

all: $(NAME) $(HEADERS)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ) 

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_PATHS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)


re: fclean all	

.PHONY: clean fclean