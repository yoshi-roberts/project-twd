CC = gcc
OPT = -O1
CFLAGS = -Wall -Wextra -std=c99 $(OPT) -I include/

ifeq ($(OS), Windows_NT)
	BUILD_RAYLIB = mingw32-make PLATFORM=PLATFORM_DESKTOP
	MKDIR = @mkdir
	RM = @rmdir /s /q
	LIBS = -L lib/raylib/src/ -lraylib -lgdi32 -lwinmm
	BIN = out.exe
else # Linux
	BUILD_RAYLIB = cd lib/raylib/src && make PLATFORM=PLATFORM_DESKTOP
	MKDIR = @mkdir -p
	RM = @rm -r
	LIBS = -L lib/raylib/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	BIN = out
endif

BIN_DIR = bin
OBJ_DIR = obj

OBJS = main.o

all: build_raylib create_dir $(BIN_DIR)/$(BIN)

create_dir:
	$(MKDIR) bin
	$(MKDIR) obj

build_raylib:
	$(BUILD_RAYLIB)

# Create executable.
$(BIN_DIR)/$(BIN): $(addprefix $(OBJ_DIR)/,$(OBJS))
	$(CC) $(LIBS) -o $@ $^ $(LIBS)

# Create object files.
$(addprefix $(OBJ_DIR),/%.o):src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) bin
	$(RM) obj