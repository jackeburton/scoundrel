CC = cc
CFLAGS = -O2           # default release flags
DEBUGFLAGS = -g -O0    # debug flags

SRC = main.c
OUT = build
DEBUG_OUT = build_debug

RAYLIB_CFLAGS  = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS    = $(shell pkg-config --libs raylib)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(RAYLIB_CFLAGS) $(RAYLIB_LIBS)

# Debug target
debug: $(SRC)
	$(CC) $(DEBUGFLAGS) $(SRC) -o $(DEBUG_OUT) $(RAYLIB_CFLAGS) $(RAYLIB_LIBS)

clean:
	rm -f $(OUT) $(DEBUG_OUT)