TARGET_EXEC ?= a.exe
CC = g++
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src


SRCS := $(wildcard ./src/**/*.cpp) $(wildcard ./src/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := SDL2/include/SDL2
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIB_DIRS = SDL2/lib
LIB_FLAGS := $(addprefix -L,$(LIB_DIRS))

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


CPPFLAGS ?= $(INC_FLAGS) $(LIB_FLAGS) -g

$(TARGET_EXEC): $(OBJS)
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(OBJS) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)  -c $< $(LDFLAGS) -o $@ 


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p