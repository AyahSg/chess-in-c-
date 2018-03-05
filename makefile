CC = gcc
OBJS = ChessArrayList.o cmdparser.o game.o setting.o minimax.o savedGames.o mainAux.o main.o \
ChessGUIManager.o ChessLoadWindow.o ChessMainWindow.o ChessSettingWindow.o GameButton.o GameWidget.o \
GameWindow.o SimpleButton.o SPCommon.o SPWindow.o Widget.o

EXEC = chessprog
CC_COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2/ -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

ChessArrayList.o: ChessArrayList.c ChessArrayList.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
cmdparser.o: cmdparser.c cmdparser.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
game.o: game.c game.h setting.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
main.o: main.c game.h mainAux.h setting.h ChessGUIManager.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
mainAux.o: mainAux.c mainAux.h minimax.h savedGames.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
minimax.o: minimax.c minimax.h game.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
savedGames.o: savedGames.c savedGames.h setting.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
setting.o: setting.c setting.h ChessArrayList.h
	$(CC) $(CC_COMP_FLAG) -c $*.c
ChessGUIManager.o: ChessGUIManager.c ChessGUIManager.h ChessMainWindow.h ChessLoadWindow.h ChessSettingWindow.h GameWindow.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessMainWindow.o: ChessMainWindow.c ChessMainWindow.h SPWindow.h SimpleButton.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessLoadWindow.o: ChessLoadWindow.c ChessLoadWindow.h SPWindow.h SimpleButton.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessSettingWindow.o: ChessSettingWindow.c ChessSettingWindow.h SPWindow.h SimpleButton.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameWindow.o: GameWindow.c GameWindow.h GameButton.h GameWidget.h setting.h minimax.h savedGames.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameWidget.o: GameWidget.c GameWidget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameButton.o: GameButton.c GameButton.h GameWidget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPCommon.o: SPCommon.c SPCommon.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPWindow.o: SPWindow.c SPWindow.h Widget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Widget.o: Widget.c Widget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SimpleButton.o: SimpleButton.c SimpleButton.h Widget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC)