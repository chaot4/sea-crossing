CC = g++
CPPFLAGS = -Wall -g -std=c++11 -DUSE_ZLIB
LFLAGS = -Wl,--no-as-needed -lGLEW -lGL -lglfw -lz

# get all .cpp files
ALL_CPP = $(wildcard **/*.cpp) $(wildcard *.cpp) 
# get source files containing "int main" 
MAIN_CPP = $(filter-out Makefile,$(shell grep "int main" * -rl))
# only non-main files are useful sources, so filter main files
SRCS_CPP = $(filter-out $(MAIN_CPP),$(ALL_CPP))
SRCS_HPP = $(wildcard **/*.h) $(wildcard *.h)
SRCS= $(SRCS_CPP) $(SRCS_HPP)

# each non-main .cpp produces an object file
OBJ = $(patsubst %.cpp,%.o,$(SRCS_CPP))
MAIN_OBJ = $(patsubst %.cpp,%.o,$(MAIN_CPP))

BIN = ../bin/main
#ALL_BIN = $(patsubst %.o,../bin/%,$(notdir $(MAIN_OBJ)))

DEPENDFILE = .depend

all: $(BIN)
	
$(BIN): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CPPFLAGS) $(LFLAGS) $(OBJ) main.o -o $@ 

dep: $(DEPENDFILE)

$(DEPENDFILE): $(SRCS)
	$(CC) -MM $(CPPFLAGS) $^ > $(DEPENDFILE)

-include $(DEPENDFILE)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(MAIN_OBJ) $(BIN)
