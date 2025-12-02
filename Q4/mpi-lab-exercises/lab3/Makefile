# Compiler
CC = mpicc
CFLAGS = -O2 -Wall

# Programs
TARGETS = hello_mpi mpi_derived_types

all: $(TARGETS)

hello_mpi: hello_mpi.c
	$(CC) $(CFLAGS) $< -o $@

mpi_derived_types: mpi_derived_types.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

