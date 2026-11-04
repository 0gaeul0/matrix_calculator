#include "matrix.h"

#include <iostream>
#include <exception>

int main() {
    try {
        // Создание исходных матриц из одномерных массивов
        double values_a[] = {1, 2, 3, 4};
        double values_b[] = {5, 6, 7, 8};

        Matrix a = matrix_from_array(values_a, 2, 2);
        Matrix b = matrix_from_array(values_b, 2, 2);

        std::cout << "Matrix A:" << std::endl;
        print_matrix(a);

        std::cout << "\nMatrix B:" << std::endl;
        print_matrix(b);

        // Сложение матриц
        Matrix sum = matrix_add(a, b);

        std::cout << "\nA + B:" << std::endl;
        print_matrix(sum);

        // Умножение матриц
        Matrix product = matrix_multiply(a, b);

        std::cout << "\nA * B:" << std::endl;
        print_matrix(product);
        // Объединение матриц по горизонтали
        Matrix combined = matrix_hstack(a, b);

        std::cout << "\nA hstack B:" << std::endl;
        print_matrix(combined);

        // Освобождение памяти
        free_matrix(a);
        free_matrix(b);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(combined);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}