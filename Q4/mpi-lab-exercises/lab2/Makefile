# Compiler
CC = mpicc
CFLAGS = -O2 -Wall

# Programs
TARGETS = \
    game_of_life-collective \
    parallel_search-collectives \
    pi_collectives \
    pi_nonblocking \
    send_recv_plus1

all: $(TARGETS)

game_of_life-collective: game_of_life-collective.c
	$(CC) $(CFLAGS) $< -o $@

parallel_search-collectives: parallel_search-collectives.c
	$(CC) $(CFLAGS) $< -o $@

pi_collectives: pi_collectives.c
	$(CC) $(CFLAGS) $< -o $@

pi_nonblocking: pi_nonblocking.c
	$(CC) $(CFLAGS) $< -o $@

send_recv_plus1: send_recv_plus1.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

