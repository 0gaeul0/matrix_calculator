#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
/**
 * @brief Создание матрицы заданного размера.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Созданная матрица с нулевыми элементами.
 * @throw std::invalid_argument Если размеры некорректны.
 * @throw std::bad_alloc Если не удалось выделить память.
 */
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = new double*[rows]();
    try {
        for (int i = 0; i < rows; ++i) {
            m.data[i] = new double[cols]();
        }
    }
    catch (...) {
        for (int i = 0; i < rows; ++i) {
            delete[] m.data[i];
        }
        delete[] m.data;
        throw;
    }
    return m;
}
/**
 * @brief Освобождение памяти матрицы.
 * @param m Матрица, память которой необходимо освободить.
 */
void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }
    for (int i = 0; i < m.rows; ++i) {
        delete[] m.data[i];
    }
    delete[] m.data;
}
/**
 * @brief Сложение двух матриц одинакового размера.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица, содержащая сумму элементов.
 * @throw std::invalid_argument Если размеры матриц не совпадают
 * или матрицы некорректны.
 */
Matrix matrix_add(Matrix a, Matrix b) {
    if (a.data == nullptr || b.data == nullptr ||
        a.rows <= 0 || a.cols <= 0 ||
        b.rows <= 0 || b.cols <= 0) {
        throw std::invalid_argument("Invalid matrix");
    }
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}
/**
 * @brief Умножение двух матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица, содержащая результат умножения.
 * @throw std::invalid_argument Если матрицы некорректны
 * или их размеры несовместимы.
 */
Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.data == nullptr || b.data == nullptr ||
        a.rows <= 0 || a.cols <= 0 ||
        b.rows <= 0 || b.cols <= 0) {
        throw std::invalid_argument("Invalid matrix");
    }
    if (a.cols != b.rows) {
        throw std::invalid_argument(
            "Number of columns of first matrix must equal number of rows of second matrix"
        );
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            for (int k = 0; k < a.cols; ++k) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}
/**
 * @brief Вывод матрицы на экран.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        throw std::invalid_argument("Invalid matrix");
    }
    std::cout << std::fixed << std::setprecision(2);
    int max_rows = (m.rows < 10) ? m.rows : 10;
    int max_cols = (m.cols < 8) ? m.cols : 8;
    for (int i = 0; i < max_rows; ++i) {
        for (int j = 0; j < max_cols; ++j) {
            std::cout << std::setw(10) << m.data[i][j];
        }
        if (m.cols > 8) {
            std::cout << " ...";
        }
        std::cout << '\n';
    }
    if (m.rows > 10) {
        std::cout << "...\n";
    }
}
/**
 * @brief Создание матрицы из одномерного массива.
 * @param data Указатель на исходный массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Созданная матрица.
 * @throw std::invalid_argument Если данные некорректны.
 */
Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr || rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid array or matrix dimensions");
    }
    Matrix result = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i * cols + j];
        }
    }
    return result;
}
/**
 * @brief Объединение двух матриц по горизонтали.
 * @param a Левая матрица.
 * @param b Правая матрица.
 * @return Новая матрица, содержащая сначала элементы a, затем b.
 * @throw std::invalid_argument Если матрицы некорректны
 * или количество строк не совпадает.
 */
Matrix matrix_hstack(Matrix a, Matrix b) {
    // Проверка корректности исходных матриц
    if (a.data == nullptr || b.data == nullptr ||
        a.rows <= 0 || a.cols <= 0 ||
        b.rows <= 0 || b.cols <= 0) {
        throw std::invalid_argument("Invalid matrix");
    }

    // Для горизонтального объединения число строк должно совпадать
    if (a.rows != b.rows) {
        throw std::invalid_argument(
            "Matrices must have the same number of rows"
        );
    }

    // Создание результирующей матрицы
    Matrix result = create_matrix(a.rows, a.cols + b.cols);

    // Копирование элементов обеих матриц
    for (int i = 0; i < a.rows; ++i) {
        // Сначала копируем строку матрицы A
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j];
        }

        // Затем копируем строку матрицы B
        for (int j = 0; j < b.cols; ++j) {
            result.data[i][a.cols + j] = b.data[i][j];
        }
    }

    return result;
}