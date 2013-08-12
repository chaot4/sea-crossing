CC = g++
CPPFLAGS = -Wall -g -std=c++11
BIN = ../bin/main
OBJ = game/game.o game/board.o
DEPENDFILE = .depend

all: $(BIN)

$(BIN): $(OBJ) main.o
	$(CC) $(CPPFLAGS) $(OBJ) main.cpp -o $(BIN)

-include $(DEPENDFILE)

.PHONY: dep
dep:
	$(CC) -MM $(CPPFLAGS) main.cpp */*.cpp */*.h > $(DEPENDFILE)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN) main.o
