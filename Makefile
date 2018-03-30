TARGET ?= run.out
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

LUA_HOME := $(HOME)/tmp/lua-5.3.4/src
GLM_HOME := $(HOME)/tmp/glm-0.9.9-a2

#INC_DIRS := $(shell find $(SRC_DIRS) -type d) $(LUA_HOME) $(GLM_HOME)
INC_DIRS := $(SRC_DIRS) $(LUA_HOME) $(GLM_HOME)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LINK_DIRS := $(LUA_HOME)
LINK_FLAGS := $(addprefix -L,$(LINK_DIRS))

LIB_FLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -lGLU -lglut -lGLEW

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++11 $(LIB_FLAGS)
LDFLAGS := $(LINK_FLAGS) `sdl2-config --libs` $(LIB_FLAGS)
CC := g++

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)