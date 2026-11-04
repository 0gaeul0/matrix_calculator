#include <gtest/gtest.h>
#include "matrix.h"
#include <sstream>
#include <iostream>

// Тест 1. Объединение двух квадратных матриц
TEST(MatrixHStackTest, CombinesSquareMatrices) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6, 7, 8};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 2, 2);

    Matrix result = matrix_hstack(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 4);

    EXPECT_DOUBLE_EQ(result.data[0][0], 1);
    EXPECT_DOUBLE_EQ(result.data[0][1], 2);
    EXPECT_DOUBLE_EQ(result.data[0][2], 5);
    EXPECT_DOUBLE_EQ(result.data[0][3], 6);

    EXPECT_DOUBLE_EQ(result.data[1][0], 3);
    EXPECT_DOUBLE_EQ(result.data[1][1], 4);
    EXPECT_DOUBLE_EQ(result.data[1][2], 7);
    EXPECT_DOUBLE_EQ(result.data[1][3], 8);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест 2. Объединение матриц с разным количеством столбцов
TEST(MatrixHStackTest, CombinesMatricesWithDifferentColumns) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 2, 1);

    Matrix result = matrix_hstack(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 3);

    EXPECT_DOUBLE_EQ(result.data[0][0], 1);
    EXPECT_DOUBLE_EQ(result.data[0][1], 2);
    EXPECT_DOUBLE_EQ(result.data[0][2], 5);

    EXPECT_DOUBLE_EQ(result.data[1][0], 3);
    EXPECT_DOUBLE_EQ(result.data[1][1], 4);
    EXPECT_DOUBLE_EQ(result.data[1][2], 6);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест 3. Объединение матриц с одним столбцом
TEST(MatrixHStackTest, CombinesSingleColumnMatrices) {
    double values_a[] = {1, 2};
    double values_b[] = {3, 4};

    Matrix a = matrix_from_array(values_a, 2, 1);
    Matrix b = matrix_from_array(values_b, 2, 1);

    Matrix result = matrix_hstack(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);

    EXPECT_DOUBLE_EQ(result.data[0][0], 1);
    EXPECT_DOUBLE_EQ(result.data[0][1], 3);
    EXPECT_DOUBLE_EQ(result.data[1][0], 2);
    EXPECT_DOUBLE_EQ(result.data[1][1], 4);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест 4. Проверка ошибки при разном количестве строк
TEST(MatrixHStackTest, ThrowsWhenRowCountsDiffer) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6, 7};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 1, 3);

    EXPECT_THROW(matrix_hstack(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

// Тест 5. Проверка ошибки при некорректной матрице
TEST(MatrixHStackTest, ThrowsForInvalidMatrix) {
    Matrix a = {nullptr, 0, 0};

    double values_b[] = {1, 2};
    Matrix b = matrix_from_array(values_b, 2, 1);

    EXPECT_THROW(matrix_hstack(a, b), std::invalid_argument);

    free_matrix(b);
}
// Тест 6. Создание матрицы с нулевой инициализацией
TEST(MatrixCreateTest, CreatesZeroInitializedMatrix) {
    Matrix m = create_matrix(2, 3);

    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 3);

    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            EXPECT_DOUBLE_EQ(m.data[i][j], 0.0);
        }
    }

    free_matrix(m);
}

// Тест 7. Проверка некорректных размеров при создании
TEST(MatrixCreateTest, ThrowsForInvalidDimensions) {
    EXPECT_THROW(create_matrix(0, 2), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, 0), std::invalid_argument);
    EXPECT_THROW(create_matrix(-1, 3), std::invalid_argument);
}

// Тест 8. Сложение двух матриц
TEST(MatrixAddTest, AddsMatricesCorrectly) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6, 7, 8};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 2, 2);

    Matrix result = matrix_add(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);

    EXPECT_DOUBLE_EQ(result.data[0][0], 6);
    EXPECT_DOUBLE_EQ(result.data[0][1], 8);
    EXPECT_DOUBLE_EQ(result.data[1][0], 10);
    EXPECT_DOUBLE_EQ(result.data[1][1], 12);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест 9. Ошибка при сложении матриц разных размеров
TEST(MatrixAddTest, ThrowsForDifferentDimensions) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 2, 1);

    EXPECT_THROW(matrix_add(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

// Тест 10. Умножение двух матриц
TEST(MatrixMultiplyTest, MultipliesMatricesCorrectly) {
    double values_a[] = {1, 2, 3, 4};
    double values_b[] = {5, 6, 7, 8};

    Matrix a = matrix_from_array(values_a, 2, 2);
    Matrix b = matrix_from_array(values_b, 2, 2);

    Matrix result = matrix_multiply(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);

    EXPECT_DOUBLE_EQ(result.data[0][0], 19);
    EXPECT_DOUBLE_EQ(result.data[0][1], 22);
    EXPECT_DOUBLE_EQ(result.data[1][0], 43);
    EXPECT_DOUBLE_EQ(result.data[1][1], 50);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест 11. Ошибка при несовместимых размерностях умножения
TEST(MatrixMultiplyTest, ThrowsForIncompatibleDimensions) {
    double values_a[] = {1, 2, 3, 4, 5, 6};
    double values_b[] = {1, 2, 3, 4};

    Matrix a = matrix_from_array(values_a, 2, 3);
    Matrix b = matrix_from_array(values_b, 2, 2);

    EXPECT_THROW(matrix_multiply(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

// Тест 12. Создание матрицы из одномерного массива
TEST(MatrixFromArrayTest, CreatesMatrixCorrectly) {
    double values[] = {1, 2, 3, 4, 5, 6};

    Matrix m = matrix_from_array(values, 2, 3);

    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 3);

    EXPECT_DOUBLE_EQ(m.data[0][0], 1);
    EXPECT_DOUBLE_EQ(m.data[0][1], 2);
    EXPECT_DOUBLE_EQ(m.data[0][2], 3);
    EXPECT_DOUBLE_EQ(m.data[1][0], 4);
    EXPECT_DOUBLE_EQ(m.data[1][1], 5);
    EXPECT_DOUBLE_EQ(m.data[1][2], 6);

    free_matrix(m);
}

// Тест 13. Проверка вывода матрицы
TEST(MatrixPrintTest, PrintsMatrixCorrectly) {
    double values[] = {1, 2, 3, 4};
    Matrix m = matrix_from_array(values, 2, 2);

    std::ostringstream output;
    std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());

    print_matrix(m);

    std::cout.rdbuf(old_buffer);

    EXPECT_NE(output.str().find("1.00"), std::string::npos);
    EXPECT_NE(output.str().find("2.00"), std::string::npos);
    EXPECT_NE(output.str().find("3.00"), std::string::npos);
    EXPECT_NE(output.str().find("4.00"), std::string::npos);

    free_matrix(m);
}
