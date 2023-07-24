CC = gcc
CFLAGS = -Wall -g -std=gnu11

INSTALL_PATH = /home/willbonner/.local/bin
BIN = gbnts

OBJS = $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) src/*.o -o $(BIN)

src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

.PHONY: clean

install:
	install -m 755 $(BIN) $(INSTALL_PATH)/$(BIN)

uninstall:
	rm -f $(INSTALL_PATH)/$(BIN)

clean:
	rm -f $(BIN)
	rm -f src/*.o
