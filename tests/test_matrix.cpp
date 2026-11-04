#include <gtest/gtest.h>
#include "matrix.h"

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
