CC = g++
CPPFLAGS = -Wall -g -std=c++11 -isystem ./../lib/
LFLAGS = -lGLEW -lGL -lglfw -lfbxsdk -L./../lib/ -Wl,-R./../lib/
BIN = ../bin/main
OBJ = conf.o game/game.o game/board.o game/player.o game/human_players.o ai/ai_players.o engine/renderHub.o engine/framebufferObject.o engine/messageReceiver.o engine/sceneCamera.o engine/texture2D.o engine/GLSLProgram.o engine/postProcessor.o engine/scene.o engine/texture3D.o engine/material.o engine/sceneEntity.o engine/mesh.o engine/resourceManager.o engine/sceneLightSource.o engine/controls.o
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
