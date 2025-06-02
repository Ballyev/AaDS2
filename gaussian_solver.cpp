#include <Eigen/Dense>
#include <stdexcept>
#include "linear_solver.h"
using namespace Eigen;
using namespace std;

VectorXd solve_linear_system(const MatrixXd &coefficients, const VectorXd &constants) {
    if (coefficients.rows() != coefficients.cols() || coefficients.rows() != constants.size()) {
        throw invalid_argument("Invalid matrix dimensions for solving");
    }

    if (coefficients.rows() == 0 || coefficients.cols() == 0) {
        throw invalid_argument("Input matrix is empty");
    }

    MatrixXd augmented(coefficients.rows(), coefficients.cols() + 1);
    augmented << coefficients, constants;

    for (Eigen::Index col = 0; col < augmented.rows(); ++col) {
        // Find pivot row
        int pivot_row = col;
        for (int row = col + 1; row < augmented.rows(); ++row) {
            if (abs(augmented(row, col)) > abs(augmented(pivot_row, col))) {
                pivot_row = row;
            }
        }


        if (pivot_row != col) {
            augmented.row(col).swap(augmented.row(pivot_row));
        }


        if (abs(augmented(col, col)) < 1e-10) {
            throw runtime_error("Matrix is singular or nearly singular");
        }


        for (int row = col + 1; row < augmented.rows(); ++row) {
            double factor = augmented(row, col) / augmented(col, col);
            augmented.row(row) -= factor * augmented.row(col);
        }

    }

        VectorXd solution(augmented.rows());
        for (int row = augmented.rows() - 1; row >= 0; --row) {
            solution(row) = augmented(row, augmented.cols() - 1);
            for (int col = row + 1; col < augmented.rows(); ++col) {
                solution(row) -= augmented(row, col) * solution(col);
            }

            solution(row) /= augmented(row, row);
        }
        return solution;
    }
