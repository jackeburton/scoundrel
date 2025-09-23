CC = cc
CFLAGS = -O2           # default release flags
DEBUGFLAGS = -g -O0    # debug flags

# Automatically include all .c files in src/
SRC = $(wildcard src/*.c)

OUT = build/build
DEBUG_OUT = build/build_debug

RAYLIB_CFLAGS  = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS    = $(shell pkg-config --libs raylib)

all: $(OUT)

# Release build
$(OUT): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(RAYLIB_CFLAGS) $(RAYLIB_LIBS)

# Debug build
debug: $(SRC)
	@mkdir -p build
	$(CC) $(DEBUGFLAGS) $(SRC) -o $(DEBUG_OUT) $(RAYLIB_CFLAGS) $(RAYLIB_LIBS)

clean:
	rm -rf $(OUT) $(DEBUG_OUT)
