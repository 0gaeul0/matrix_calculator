#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура для хранения матрицы.
 */
typedef struct {
    double** data;  // Указатель на двумерный массив
    int rows;       // Количество строк
    int cols;       // Количество столбцов
} Matrix;

/**
 * @brief Создание матрицы заданного размера.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти матрицы.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение двух матриц.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы на экран.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из одномерного массива.
 */
Matrix matrix_from_array(double* data, int rows, int cols);
/**
 * @brief Объединение двух матриц по горизонтали.
 * @param a Левая матрица.
 * @param b Правая матрица.
 * @return Новая матрица, содержащая сначала элементы a, затем b.
 * @throw std::invalid_argument Если матрицы некорректны
 * или количество строк не совпадает.
 */
Matrix matrix_hstack(Matrix a, Matrix b);
#endif // MATRIX_H
