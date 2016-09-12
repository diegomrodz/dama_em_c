CC=gcc
STD=c11
TESTS=test/
LIBS=$(wildcard lib/*)
INCLUDE_PATH=lib/

build: libs
	$(CC) -std=$(STD) -W -Wall main.c $(wildcard src/*) -I$(INCLUDE_PATH) -o dama -lm -lSDL -lSDL_image -lSDL_ttf

libs:
	mkdir src/
	for dir in $(LIBS); do \
		cd $$dir; \
		gcc -c *.c -I../; \
		mv *.o ../../src; \
		cd -; \
	done;

clean:
	rm -rf src/