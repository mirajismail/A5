#include <iostream>
#include <cmath>
#include <rarray>


// This program will simulate the Diffusion process in 2D
// we will start with an N_x by N_y grid of temperatures u.
// f[i][j] represents the temperature at position (i, j) at the current time.
// f is initialized with 1 hotspot in the center (indicated by 1.0 temperature) and the remainder of
// the grid is cold (indicated by 0.0 temperature)
// we will represent the physical size of the region as a len_x by len_y space
// hence, delta_x and delta_y will be the size of the respective dimension, divided by the number of grid points in that dimension
int main() {
    // Grid parameters
    const int N_x = 50;
    const int N_y = 50;

    // Dimensions of the physical space
    const double len_x = 1.0;
    const double len_y = 1.0;

    const double delta_x = len_x / (N_x - 1);
    const double delta_y = len_y / (N_y - 1);

    // Diffusion parameters
    const double D = 0.01;
    const double delta_t = 0.0001;

    const double rx = D * delta_t / (delta_x * delta_x);
    const double ry = D * delta_t / (delta_y * delta_y);

    // rarray representing the field f_(i,j)
    rarray<double,2> f(N_x, N_y);
    rarray<double,2> f_new(N_x, N_y);

    // initialize field
    for (int i = 0; i < N_x; i++) {
        for (int j = 0; j < N_y; j++) {
            f[i][j] = 0.0;
        }
    }

    // hot spot in center
    int cx = N_x / 2;
    int cy = N_y / 2;
    f[cx][cy] = 1.0;

    // simulation
    const int steps = 20000;

    for (int n = 0; n < steps; n++) {
        // interior update
        for (int i = 1; i < N_x - 1; i++) {
            for (int j = 1; j < N_y - 1; j++) {
                f_new[i][j] = f[i][j]
                    + rx * (f[i+1][j] - 2.0*f[i][j] + f[i-1][j])
                    + ry * (f[i][j+1] - 2.0*f[i][j] + f[i][j-1]);
            }
        }

        // boundaries = zero Dirichlet
        for (int i = 0; i < N_x; i++) {
            f_new[i][0] = 0.0;
            f_new[i][N_y-1] = 0.0;
        }
        for (int j = 0; j < N_y; j++) {
            f_new[0][j] = 0.0;
            f_new[N_x-1][j] = 0.0;
        }

        // swap arrays
        std::swap(f, f_new);

        // check change in temperature at the center of the grid every 1000 steps
        if (n % 1000 == 0) {
            std::cout << "step " << n
                      << " | center = " << f[cx][cy] << "\n";
        }
    }

    std::cout << "Simulation complete.\n";
    return 0;
}

