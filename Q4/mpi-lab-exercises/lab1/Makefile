# Compiler
CC = mpicc
CFLAGS = -O2 -Wall

# Programs
TARGETS = \
    pi_mpi \
    send_recv_mpi \
    hello_mpi \
    parallel_search_mpi \
    game_of_life_mpi

all: $(TARGETS)

pi_mpi: pi_mpi.c
	$(CC) $(CFLAGS) $< -o $@

send_recv_mpi: send_recv_mpi.c
	$(CC) $(CFLAGS) $< -o $@

hello_mpi: hello_mpi.c
	$(CC) $(CFLAGS) $< -o $@

parallel_search_mpi: parallel_search_mpi.c
	$(CC) $(CFLAGS) $< -o $@

game_of_life_mpi: game_of_life_mpi.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

