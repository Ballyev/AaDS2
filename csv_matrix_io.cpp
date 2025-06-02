#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>
#include "linear_solver.h"
using namespace Eigen;
using namespace std;

MatrixXd read_matrix_from_csv(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    vector<vector<double>> matrix_data;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<double> row;

        while (getline(ss, cell, ',')) {
            row.push_back(stod(cell));
        }

        matrix_data.push_back(row);
    }

    if (matrix_data.empty()) return MatrixXd();

    MatrixXd matrix(matrix_data.size(), matrix_data[0].size());
    for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = matrix_data[i][j];
        }
    }

        return matrix;
    }

    void write_matrix_to_csv(const string& filename, const MatrixXd& matrix) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing: " + filename);
        }

        for (int i = 0; i < matrix.rows(); ++i) {
            for (int j = 0; j < matrix.cols(); ++j) {
                file << matrix(i, j);
                if (j != matrix.cols() - 1) file << ",";
            }
            file << endl;
        }
    }