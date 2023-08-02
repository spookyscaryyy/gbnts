CC = gcc
CFLAGS = -Wall -g -std=gnu11
CHECK = `pkg-config --cflags --libs check`

INSTALL_PATH = /home/willbonner/.local/bin
BIN = gbnts
TBIN = unit

SRC_DIR = src
TEST_DIR = test

SOURCES := $(wildcard $(SRC_DIR)/*.c $(TEST_DIR)/*.c)
SOURCES := $(notdir $(SOURCES))
SOURCES := $(patsubst %.c,%.o, $(SOURCES))
SOURCES := $(filter-out src/main.c, $(SOURCES))

OBJS = $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
TOBJS = $(patsubst test/%.c,test/%.o,$(wildcard test/*.c))

TEST := $(patsubst %, $(OBJS), $(TOBJS))
TEST := $(filter-out src/main.c, $(TEST))

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) src/*.o -o $(BIN)

src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

test/%.o: test/%.c test/%.h
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

.PHONY: clean test

install:
	make
	install -m 755 $(BIN) $(INSTALL_PATH)/$(BIN)

uninstall:
	rm -f $(INSTALL_PATH)/$(BIN)

clean:
	rm -f $(BIN)
	rm -f $(TBIN)
	rm -f src/*.o
	rm -f test/*.o

test: $(TEST)
	$(CC) $(CFLAGS) $^ -o $(TBIN) $(CHECK)
	./unit
