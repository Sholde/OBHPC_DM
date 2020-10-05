CC = gcc

CFLAGS = -g3 -Wall

OFLAGS = -O0

all: clean rdp

rdp: src/main.c
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $@

opti: src/main.c
	$(CC) $(CFLAGS) -Ofast $^ -o $@

tests: rdp
	@ ./$^ -r 5 out_a_5.txt
	@ ./$^ -r 5 out_b_5.txt
	@ ./$^ -c 5 out_a_5.txt out_b_5.txt out_c_5.txt
	@ ./$^ -r 10 out_a_10.txt
	@ ./$^ -r 10 out_b_10.txt
	@ ./$^ -c 10 out_a_10.txt out_b_10.txt out_c_10.txt
	@ ./$^ -r 50 out_a_50.txt
	@ ./$^ -r 50 out_b_50.txt
	@ ./$^ -c 50 out_a_50.txt out_b_50.txt out_c_50.txt
	@ ./$^ -r 100 out_a_100.txt
	@ ./$^ -r 100 out_b_100.txt
	@ ./$^ -c 100 out_a_100.txt out_b_100.txt out_c_100.txt



clean:
	rm -Rf *~ rdp out*
