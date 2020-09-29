CC = gcc

CFLAGS = -g3 -W

OFLAGS = -O0

EXE = main

all: clean $(EXE)

$(EXE): main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

clean:
	rm -Rf *~ $(EXE)
