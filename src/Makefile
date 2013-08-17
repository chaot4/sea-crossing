CC = g++
CPPFLAGS = -Wall -g -std=c++11 -I./../lib/
LFLAGS = -lGLEW -lGL -lglfw -L./../lib/ -Wl,-R./../lib/
BIN = ../bin/main
OBJ = game/game.o game/board.o game/player.o game/human_players.o ai/ai_players.o engine/renderHub.o
DEPENDFILE = .depend

all: $(BIN)

$(BIN): $(OBJ) main.o
	$(CC) $(CPPFLAGS) $(LFLAGS) $(OBJ) main.cpp -o $(BIN)

-include $(DEPENDFILE)

.PHONY: dep
dep:
	$(CC) -MM $(CPPFLAGS) main.cpp game/*.cpp game/*.h ai/*.cpp ai/*.h > $(DEPENDFILE)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN) main.o
