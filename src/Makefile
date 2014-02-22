CC = g++
CPPFLAGS = -Wall -g -std=c++11 -DUSE_ZLIB
LFLAGS = -Wl,--no-as-needed -lGLEW -lGL -lglfw -lz
BIN = ../bin/main
OBJ = conf.o messageChannel.o communicationHub.o ioCenter.o messages.o\
	game/game.o game/board.o game/player.o game/human_players.o game/game_center.o game/player_center.o \
	ai/ai_players.o \
	engine/renderHub.o engine/framebufferObject.o engine/messageReceiver.o \
	engine/sceneCamera.o engine/texture2D.o engine/GLSLProgram.o engine/postProcessor.o \
	engine/scene.o engine/texture3D.o engine/material.o engine/mesh.o \
	engine/resourceManager.o engine/sceneLightSource.o engine/controls.o \
	engine/renderGraph.o engine/staticSceneObject.o  \
	fbx/fbx_reader.o fbx/fbx_unzip.o fbx/fbx_node_name.o fbx/fbx_parser.o \
	fbx/fbx_property.o fbx/fbx_value.o fbx/fbx_print.o fbx/fbx_geometry.o \
	fbx/fbx_opengl_geometry.o
SRCS = $(wildcard **/*.cpp) $(wildcard **/*.h) $(wildcard *.cpp) $(wildcard *.h)
DEPENDFILE = .depend

all: $(BIN)

$(BIN): $(OBJ) main.o
	$(CC) $(CPPFLAGS) $(LFLAGS) $(OBJ) main.cpp -o $(BIN)

dep: $(DEPENDFILE)

$(DEPENDFILE): $(SRCS)
	$(CC) -MM $(CPPFLAGS) $^ > $(DEPENDFILE)

-include $(DEPENDFILE)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN) main.o
