SDL_DIR=SDL/x86_64-w64-mingw32

x86_64-w64-mingw32-gcc.exe -Iincludes srcs/main.c libmlx.a \
-L"$SDL_DIR/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer \
-lSDL2_ttf  -lmingw32 -lSDL2main -lSDL2.dll -luser32 -lgdi32 -lwinmm -ldxguid -o test.exe