CC = gcc
CFLAGS = -Wall -g -std=gnu11 --coverage
CHECK = `pkg-config --cflags --libs check`

INSTALL_PATH = /home/willbonner/.local/bin
BIN = gbnts
TBIN = unit

SRC_DIR = src
TEST_DIR = test

OBJS = $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
TOBJS = $(patsubst test/%.c,test/%.o,$(wildcard test/*.c))


$(BIN): $(OBJS)
	$(CC) $(CFLAGS) src/*.o -o $(BIN)

src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

test/%.o: test/%.c test/%.h
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

.PHONY: clean test coverage

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
	rm -f src/*.gcno
	rm -f test/*.gcno
	rm -f test/*.gcda
	rm -f src/*.gch
	rm -f src/*.gcda

test: $(filter-out src/main.o, $(OBJS)) $(TOBJS)
	$(CC) $(CFLAGS) $^ -o $(TBIN) $(CHECK)

coverage:
	make
	./unit
	gcovr
