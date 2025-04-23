#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
public:
    // Конструктор для инициализации матрицы
    Matrix(const std::vector<std::vector<double>>& mat);

    Matrix(int n, double initialValue = 0.0);  // Конструктор для создания матрицы размера n x n

    // Функция для вывода матрицы
    void printMatrix() const;
    void printMatrix(const std::vector<double>& b) const;

    // Функция для нахождения обратной матрицы методом Гаусса
    Matrix inverse() const;

    // Функция для решения СЛАУ методом Гаусса
    std::vector<double> solveGauss(const std::vector<double>& b) const;

    // Функция для нахождения определителя матрицы методом Гаусса
    double determinant() const;

    // Функция для нахождения LU-разложения матрицы
    void LU_decomposition(Matrix& L, Matrix& U) const;

    // Функция для решения СЛАУ методом LU-разложения
    std::vector<double> solveLU(const std::vector<double>& b) const;

    // Функция для нахождения определителя методом LU-разложения
    double determinantLU() const;

    // Функция для оценки погрешности правой части после решения СЛАУ
    double estimateError(const std::vector<double>& b, const std::vector<double>& x) const;


private:
    std::vector<std::vector<double>> a;  // Матрица
    int n;                               // Размерность матрицы
};

#endif // MATRIX_H
