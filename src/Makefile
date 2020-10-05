CC = gcc

CFLAGS = -g3 -Wall

OFLAGS = -O0

all: clean rdp

rdp: main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

opti: main.c
	$(CC) $(CFLAGS) -Ofast $^ -o $@

tests: rdp
	@ ./$^ 5 out5
	@ ./$^ 10 out10
	@ ./$^ 50 out50
	@ ./$^ 100 out100

clean:
	rm -Rf *~ rdp out*
