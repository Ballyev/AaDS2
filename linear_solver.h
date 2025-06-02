#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include <Eigen/Dense>
#include <string>

using namespace Eigen;
using namespace std;


MatrixXd read_matrix_from_csv(const string& filename);
void write_matrix_to_csv(const string& filename, const MatrixXd& matrix);


VectorXd solve_linear_system(const MatrixXd& coefficients, const VectorXd& constants);


void generate_random_system(int size, const string& filename, unsigned int seed);

#endif // LINEAR_SOLVER_H
