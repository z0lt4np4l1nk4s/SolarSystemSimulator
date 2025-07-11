# Cross‑platform Makefile for SolarSystemSimulator
# ------------------------------------------------
#   Linux   : sudo apt install build-essential libglfw3-dev
#   macOS   : brew install glfw
#   Windows : build iz **MSYS2 MinGW 64‑bit shella** → pacman -S mingw-w64-x86_64-glfw
#             (ili ručno staviti glfw3.dll /.a u ./lib i header‑e u ./include/GLFW)
#
# Targets
#   make          – build
#   make run      – build & run
#   make clean    – remove objects & binary

# ---------- project settings ----------
TARGET      := SolarSystemSimulator
CXX         ?= g++
CC          ?= gcc
CXXFLAGS    := -std=c++17 -O2 -Wall -Wextra -Iinclude
CFLAGS      := -std=c11   -O2 -Wall -Wextra -Iinclude
OBJDIR      := build

# ---------- source files -------------
CPP_SOURCES := $(wildcard main.cpp) \
               $(wildcard src/*.cpp) \
               $(wildcard src/models/*.cpp)
C_SOURCES   := src/glad.c
SOURCES     := $(CPP_SOURCES) $(C_SOURCES)
OBJECTS     := $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
OBJECTS     := $(OBJECTS:.c=.o)

# ---------- platform detection -------
ifeq ($(OS),Windows_NT)
    PLATFORM := Windows
else
    PLATFORM := $(shell uname -s)
endif

# ---------- mkdir / rm / null ---------
ifeq ($(PLATFORM),Windows)
    NULL  := nul
    RMDIR := rmdir /S /Q
else
    NULL  := /dev/null
    RMDIR := rm -rf
endif

# Tiny function for mkdir‑p that zna slashes
# $(call MKDIR_P,<path>)
ifeq ($(PLATFORM),Windows)
    define MKDIR_P
	cmd /C "if not exist \"$(subst /,\\,$1)\" mkdir \"$(subst /,\\,$1)\""
    endef
else
    define MKDIR_P
	mkdir -p $1
    endef
endif

# ---------- library & linker flags ---
ifeq ($(PLATFORM),Linux)
    LIBS := $(shell pkg-config --static --libs glfw3 2>$(NULL) || echo "-lglfw") -ldl -lGL -pthread
endif

ifeq ($(PLATFORM),Darwin)
    LIBS := -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

ifeq ($(PLATFORM),Windows)
    LIBDIRS := -Llib
    INCDIRS := -Iinclude
    LIBS    := -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
    CXXFLAGS += $(INCDIRS)
    CFLAGS   += $(INCDIRS)
endif

# ---------- rules --------------------
.PHONY: all clean run

all: $(TARGET)

# link step
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LIBDIRS) $(LIBS) -o $@

# compile cpp
$(OBJDIR)/%.o: %.cpp
ifeq ($(PLATFORM),Windows)
	@if not exist "$(subst /,\,$(patsubst %/,%, $(dir $@)))" mkdir "$(subst /,\,$(patsubst %/,%, $(dir $@)))"
else
	@mkdir -p $(patsubst %/,%, $(dir $@))
endif
	$(CXX) $(CXXFLAGS) -c $< -o $@

# compile c
$(OBJDIR)/%.o: %.c
ifeq ($(PLATFORM),Windows)
	@if not exist "$(subst /,\,$(patsubst %/,%, $(dir $@)))" mkdir "$(subst /,\,$(patsubst %/,%, $(dir $@)))"
else
	@mkdir -p $(patsubst %/,%, $(dir $@))
endif
	$(CC) $(CFLAGS)   -c $< -o $@

# END compile rules


$(OBJDIR)/%.o: %.c
	-@$(call MKDIR_P,$(patsubst %/,%, $(dir $@))) >$(NULL) 2>&1
	$(CC) $(CFLAGS)   -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	-@$(RMDIR) $(OBJDIR) 2>$(NULL)
	-@$(RMDIR) $(TARGET) 2>$(NULL)
