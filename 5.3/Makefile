CC = gcc

CFLAGS = -g3 -Wall

OFLAGS = -O0

all: clean rdc

rdc: main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

opti: main.c
	$(CC) $(CFLAGS) -Ofast $^ -o $@

tests: rdc
	@ ./rdc 5 out5
	@ ./rdc 10 out10
	@ ./rdc 50 out50
	@ ./rdc 100 out100

clean:
	rm -Rf *~ rdc out*
