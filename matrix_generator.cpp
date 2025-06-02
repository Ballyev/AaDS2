#include <Eigen/Dense>
#include <random>
#include <string>
#include "linear_solver.h"
using namespace Eigen;
using namespace std;

void generate_random_system(int size, const string& filename, unsigned int seed = 42) {
    mt19937 random_engine(seed);
    uniform_real_distribution<double> distribution(-10.0, 10.0);

    MatrixXd coefficients(size, size);
    VectorXd constants(size);

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            coefficients(row, col) = distribution(random_engine);
        }
        constants(row) = distribution(random_engine);
    }

    MatrixXd combined(size, size + 1);
    combined << coefficients, constants;

    write_matrix_to_csv(filename, combined);
}