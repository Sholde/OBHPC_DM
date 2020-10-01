CC = gcc

CFLAGS = -g3 -Wall

OFLAGS = -O0

all: clean rdc

rdc: main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

opti: main.c
	$(CC) $(CFLAGS) -Ofast $^ -o $@

clean:
	rm -Rf *~ rdc opti output.txt
