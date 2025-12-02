# Ants on table modularize

make or make antsontable — build the executable

make clean — remove object files, executable, and output file

1. linear.* — Linear Indexing
Purpose

Provides the linear() function that converts (row, col) coordinates into a 1D index for a flattened array.

2. partition.* — Random Ant Distribution
Purpose

Given a number of ants in a square, this module randomly partitions them into 9 move directions.

3. init.* — Initial Ant Placement
Purpose

Places ants evenly across the table at simulation start.

4. timestep.* — Single Simulation Update
Purpose

Performs one full timestep:

Clears the auxiliary grid

Partitions ants at each square

Moves the ants to their new positions

Copies the updated grid back into the main grid

5. output.* — I/O and Statistics
Purpose

Handles file output and computing statistics on the ant grid.

Main Driver (main.cpp)
Responsibilities

Set simulation parameters (table size, timestep count, total ants)

Allocate arrays dynamically

Initialize the ant distribution

Iterate over all timesteps

Record output to console and file

Free all allocated memory
