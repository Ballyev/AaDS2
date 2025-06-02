#include <iostream>
#include <string>
#include "linear_solver.h"
using namespace std;


MatrixXd read_matrix_from_csv(const string& filename);
void write_matrix_to_csv(const string& filename, const MatrixXd& matrix);
VectorXd solve_linear_system(const MatrixXd& coefficients, const VectorXd& constants);
void generate_random_system(int size, const string& filename, unsigned int seed = 42);
void run_all_tests();

int main(int argc, char** argv) {
    if (argc > 1 && string(argv[1]) == "--test") {
        run_all_tests();
        return 0;
    }

    if (argc > 1 && string(argv[1]) == "--generate") {
        int size = argc > 2 ? stoi(argv[2]) : 100;
        string filename = argc > 3 ? argv[3] : "random_system.csv";
        generate_random_system(size, filename);
        cout << "Generated " << size << "x" << size << " system in " << filename << "\n";
        return 0;
    }

    if (argc < 2) {
        cout << "Usage:\n"
             << "  " << argv[0] << " --test\n"
             << "  " << argv[0] << " --generate [size] [filename]\n"
             << "  " << argv[0] << " input.csv\n";
        return 1;
    }

    try {
        MatrixXd system = read_matrix_from_csv(argv[1]);
        int size = system.rows();
        VectorXd solution = solve_linear_system(
            system.leftCols(size),
            system.rightCols(1)
        );

        write_matrix_to_csv("solution.csv", solution);
        cout << "Solution saved to solution.csv\n";
        cout << "Solution vector:\n" << solution.transpose() << "\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}