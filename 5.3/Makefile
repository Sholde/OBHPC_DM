CC = gcc

CFLAGS = -g3 -Wall

OFLAGS = -O0

all: clean rdc

rdc: main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

opti: main.c
	$(CC) $(CFLAGS) -Ofast $^ -o $@

tests: rdc
	@ echo "Size = 5" && ./rdc 5 out5 > perf.txt
	@ echo "" >> perf.txt
	@ echo "Size = 10" && ./rdc 10 out10 >> perf.txt
	@ echo "" >> perf.txt
	@ echo "Size = 50" && ./rdc 50 out50 >> perf.txt
	@ echo "" >> perf.txt
	@ echo "Size = 100" && ./rdc 100 out100 >> perf.txt

clean:
	rm -Rf *~ rdc out*
