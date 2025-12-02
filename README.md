# A5


First load gcc 14.3 and then openmpi 5.0.8
module load gcc/14.3
module load openmpi/5.0.8

## Q1
- Compute-bound:
MPI is a very good fit. Split the work across ranks, keep communication small, scale to many nodes.

- Memory-capacity-bound:
Also a very good use-case. MPI lets us pool RAM across many nodes when one machine can’t hold the dataset.

- Memory-bandwidth-bound:
Still viable. Each rank gets its own local memory channels. Works well if communication stays low.

- Communication-bound:
MPI can do it, but scaling is usually bad. Too many small or frequent messages kill performance.

- I/O-bound:
Very good fit when using MPI-IO + parallel file systems. Lets many ranks read/write one big file efficiently.

So MPI is best for compute-heavy or memory-heavy distributed workloads, okay for bandwidth-heavy, and weaker for communication-heavy algorithms.

## Q2
1. MPI compilers are not actually compilers but rather front-end wrapper scripts around the system's actual compiler (gcc, g++, clang). Technically, what mpicc does for example, is call gcc and injects the correct OpenMPI or MPICH flags so the user doesn't have to.

2. 
- mpicc --show

    Shows the exact compile command used (the underlying compiler + all flags).
- mpicc --version

    Shows the Open MPI version and underlying compiler version.

- ompi_info 

    dumps the entire MPI installation config.

- ompi-info --config

    Show OpenMPI build configuration

3. There are 10 MPI versions available on teach with the following configs:

    for openMPI:
    ```
    MODULE        PARENT(S)
        1  openmpi/5.0.3 StdEnv/2023 nvhpc/25.1
        2  openmpi/4.1.5 StdEnv/2023 nvhpc/23.9
        3  openmpi/5.0.8 StdEnv/2023 llvm/21.1.5
        4  openmpi/5.0.8 StdEnv/2023 intel/2025.2.0
        5  openmpi/5.0.3 StdEnv/2023 intel/2024.2.0
        6  openmpi/4.1.5 StdEnv/2023 intel/2023.2.1
        7  openmpi/5.0.8 StdEnv/2023 gcc/14.3
        8  openmpi/5.0.3 StdEnv/2023 gcc/13.3
        9  openmpi/4.1.5 StdEnv/2023 gcc/12.3
        10 openmpi/4.1.4 StdEnv/2020 nvhpc/23.7
        11 openmpi/4.1.1 StdEnv/2020 nvhpc/22.7 cuda/11.4
        12 openmpi/4.1.4 StdEnv/2020 nvhpc/22.7
        13 openmpi/4.1.1 StdEnv/2020 nvhpc/22.7
        14 openmpi/4.1.1 StdEnv/2020 nvhpc/22.1 cuda/11.4
        15 openmpi/4.1.4 StdEnv/2020 nvhpc/22.1
        16 openmpi/4.1.1 StdEnv/2020 nvhpc/22.1
        17 openmpi/4.0.3 StdEnv/2020 nvhpc/20.7 cuda/11.0
        18 openmpi/4.0.3 StdEnv/2020 nvhpc/20.7
        19 openmpi/4.1.4 StdEnv/2020 intel/2022.1.0
        20 openmpi/4.1.1 StdEnv/2020 intel/2021.2.0
        21 openmpi/4.0.3 StdEnv/2020 intel/2020.1.217 cuda/11.7
        22 openmpi/4.0.3 StdEnv/2020 intel/2020.1.217 cuda/11.4
        23 openmpi/4.0.3 StdEnv/2020 intel/2020.1.217 cuda/11.2.2
        24 openmpi/4.0.3 StdEnv/2020 intel/2020.1.217 cuda/11.0
        25 openmpi/4.0.3 StdEnv/2020 intel/2020.1.217
        26 openmpi/4.0.3 StdEnv/2020 gcc/9.3.0 cuda/11.7
        27 openmpi/4.0.3 StdEnv/2020 gcc/9.3.0 cuda/11.4
        28 openmpi/4.0.3 StdEnv/2020 gcc/9.3.0 cuda/11.2.2
        29 openmpi/4.0.3 StdEnv/2020 gcc/9.3.0 cuda/11.0
        30 openmpi/4.0.3 StdEnv/2020 gcc/9.3.0
        31 openmpi/4.0.3 StdEnv/2020 gcc/8.4.0 cuda/10.2
        32 openmpi/4.1.4 StdEnv/2020 gcc/11.3.0
        33 openmpi/4.1.1 StdEnv/2020 gcc/10.3.0
        34 openmpi/4.0.5 StdEnv/2020 gcc/10.3.0
        35 openmpi/4.1.1 StdEnv/2020 gcc/10.2.0
        36 openmpi/4.0.5 StdEnv/2020 gcc/10.2.0
    ```
    for intel:
    ```
    MODULE              PARENT(S)
    1  intelmpi/2021.9.0   StdEnv/2023 intel/2023.2.1
    2  intelmpi/2021.2.0   StdEnv/2020 intel/2021.2.0
    3  intelmpi/2019.7.217 StdEnv/2020 intel/2020.1.217
    ```
    There are 7 openMPI and 3 intel MPI releases, built against many different compiler toolchains.

4. 
    For the newest OpenMPI release, use `StdEnv/2023  gcc/14.3  openmpi/5.0.8`
    
## Q3
Solution is in the `Q3` directory

## Q4

solutions to lab 1 are in Q4/mpi-lab-exercises/lab1 in

- hello\_mpi.c
- send\_recv\_mpi.c
- pi\_mpi.c
- parallel\_search\_mpi.c
- game\_of\_life\_mpi.c

To compile, simply run `make`, and the executables will have the names of their respective c files.

Solutions to lab 2 are in 
Q4/mpi-lab-exercises/lab2 in
- pi\_collectives.c
- pi\_nonblocking.c
- send\_recv\_plus1.c
- parallel\_search-collectives.c
- game\_of\_life-collectives.c

To compile, simply run `make`, and the executables will have the names of their respective c files.

Solutions to lab 3 are in Q4/mpi-lab-exercises/lab3 in
- hello\_mpi.c
- mpi\_derived\_types.c

To compile, simply run `make`, and the executables will have the same names of their respective c files.

## Q5 Ants on a table
The solution to Ants on a table is in the `anstontable-miraj-solution` and the documentation is in the `README.md` file.

