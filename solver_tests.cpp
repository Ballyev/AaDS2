#include <Eigen/Dense>
#include <iostream>
#include <string>
#include "linear_solver.h"

using namespace Eigen;
using namespace std;

void test_small_system() {
    cout << "[Test] Small system...\n";
    Matrix2d A;
    Vector2d b(3, 9);
    Vector2d expected(4, 5);

    A << 2, -1,
         1,  1;

    Vector2d solution = solve_linear_system(A, b);

    if (!solution.isApprox(expected, 1e-6)) {
        cerr << "Small system test failed!\n";
        cerr << "Expected: " << expected.transpose() << "\n";
        cerr << "Got:      " << solution.transpose() << "\n";
    } else {
        cout << "Small system test passed\n";
    }
}

void test_pivot_required() {
    cout << "[Test] Pivot required...\n";
    Matrix3d A;
    Vector3d b(5, 6, 7);
    Vector3d expected(1, 2, 3);

    A << 0, 1, 2,
         1, 1, 1,
         2, 1, 0;

    try {
        Vector3d solution = solve_linear_system(A, b);

        if (!solution.isApprox(expected, 1e-6)) {
            cerr << "Pivot test failed!\n";
            cerr << "Expected: " << expected.transpose() << "\n";
            cerr << "Got:      " << solution.transpose() << "\n";
        } else {
            cout << "Pivot test passed\n";
        }

    } catch (const exception& e) {
        cerr << "Exception in pivot test: " << e.what() << "\n";
    }
}

void test_singular_matrix() {
    cout << "[Test] Singular matrix...\n";
    Matrix3d A = Matrix3d::Zero();
    Vector3d b = Vector3d::Ones();

    try {
        VectorXd solution = solve_linear_system(A, b);
        cerr << "Singular matrix test failed: no exception thrown\n";
    } catch (const exception& e) {
        cout << "Singular matrix test passed (caught): " << e.what() << "\n";
    }
}

void test_empty_input() {
    cout << "[Test] Empty input...\n";
    MatrixXd A;
    VectorXd b;

    try {
        VectorXd solution = solve_linear_system(A, b);
        cerr << "Empty input test failed: no exception thrown\n";
    } catch (const exception& e) {
        cout << "Empty input test passed (caught): " << e.what() << "\n";
    }
}

void test_hilbert_matrix() {
    cout << "[Test] Hilbert matrix...\n";
    const int size = 4;
    MatrixXd A(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A(i, j) = 1.0 / (i + j + 1);
        }
    }

    VectorXd b = A * VectorXd::Ones(size); // Ax = [1,1,1,1]^T

    try {
        VectorXd solution = solve_linear_system(A, b);
        if (!solution.isApprox(VectorXd::Ones(size), 1e-5)) {
            cerr << "Hilbert matrix test failed!\n";
            cerr << "Expected: " << VectorXd::Ones(size).transpose() << "\n";
            cerr << "Got:      " << solution.transpose() << "\n";
        } else {
            cout << "Hilbert matrix test passed\n";
        }
    } catch (const exception& e) {
        cerr << "Exception in Hilbert test: " << e.what() << "\n";
    }
}

void run_all_tests() {
    cout << " RUNNING TESTS\n";


    test_small_system();
    test_pivot_required();
    test_singular_matrix();
    test_empty_input();
    test_hilbert_matrix();
}