CC = g++
CPPFLAGS = -Wall -g -std=c++11 -isystem ./../lib/
LFLAGS = -lGLEW -lGL -lglfw -lfbxsdk -L./../lib/ -Wl,-R./../lib/ -lz
BIN = ../bin/main
OBJ = conf.o \
	game/game.o game/board.o game/player.o game/human_players.o \
	ai/ai_players.o \
	engine/renderHub.o engine/framebufferObject.o engine/messageReceiver.o engine/sceneCamera.o engine/texture2D.o engine/GLSLProgram.o \
	engine/postProcessor.o engine/scene.o engine/texture3D.o engine/material.o engine/sceneEntity.o engine/mesh.o \
	engine/resourceManager.o engine/sceneLightSource.o engine/controls.o \
	fbx/fbx_reader.o fbx/fbx_unzip.o fbx/fbx_node_name.o fbx/fbx_parser.o \
	fbx/fbx_property.o fbx/fbx_value.o fbx/fbx_print.o fbx/fbx_geometry.o fbx/fbx_opengl_geometry.o
DEPENDFILE = .depend

all: $(BIN)

$(BIN): $(OBJ) main.o
	$(CC) $(CPPFLAGS) $(LFLAGS) $(OBJ) main.cpp -o $(BIN)

-include $(DEPENDFILE)

.PHONY: dep
dep:
	$(CC) -MM $(CPPFLAGS) main.cpp game/*.cpp game/*.h ai/*.cpp ai/*.h fbx/*.cpp fbx/*.hpp > $(DEPENDFILE)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN) main.o
