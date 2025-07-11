# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -I./include

SRC := main.cpp src/glad.c $(wildcard src/*.cpp) $(wildcard src/models/*.cpp)

ifeq ($(OS), Windows_NT)
    TARGET := out.exe
    LDFLAGS := -L./lib
    LDLIBS := -lglfw3 -lgdi32 -lopengl32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        TARGET := out
        LDFLAGS :=
        LDLIBS := -lglfw -lGL -ldl -lX11 -lpthread
    endif
    ifeq ($(UNAME_S), Darwin)
        TARGET := out
        LDFLAGS :=
        LDLIBS := -lglfw -framework OpenGL
    endif
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f out out.exe *.o
