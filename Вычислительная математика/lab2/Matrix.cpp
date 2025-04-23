#include "Matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Конструктор для инициализации матрицы
Matrix::Matrix(const vector<vector<double>>& mat) : a(mat), n(mat.size()) {}

// Реализация конструктора для создания матрицы n x n, заполненной initialValue
Matrix::Matrix(int n, double initialValue) : n(n), a(n, std::vector<double>(n, initialValue)) {}


// Реализация функции вывода матрицы
void Matrix::printMatrix(const vector<double>& b) const {
    int width = 10;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Выводим каждый элемент с фиксированной шириной и 3 знаками после запятой
            cout << setw(width) << fixed << setprecision(3) << a[i][j] << " ";
        }
        // Выводим элементы вектора b в конце каждой строки матрицы
        cout << "| " << setw(width) << fixed << setprecision(3) << b[i] << endl;
    }
    cout << endl;
}


// Реализация функции вывода матрицы
void Matrix::printMatrix() const {
    int width = 10;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(width) << fixed << setprecision(3) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Реализация функции нахождения обратной матрицы
Matrix Matrix::inverse() const {
    vector<vector<double>> a_copy = a;  // Копия матрицы
    vector<vector<double>> inv(n, vector<double>(n, 0));

    // Создаем расширенную матрицу [A|I]
    for (int i = 0; i < n; ++i) {
        inv[i][i] = 1.0;  // единичная матрица
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента для выбора главного элемента
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(a_copy[k][i]) > abs(a_copy[max_row][i])) {
                max_row = k;
            }
        }

        // Меняем строки местами в обоих матрицах (A и единичная часть)
        swap(a_copy[i], a_copy[max_row]);
        swap(inv[i], inv[max_row]);

        // Нормализуем строку, делая главный элемент равным 1
        double diag_elem = a_copy[i][i];
        for (int j = 0; j < n; ++j) {
            a_copy[i][j] /= diag_elem;
            inv[i][j] /= diag_elem;
        }

        // Обнуление элементов ниже и выше главного элемента
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = a_copy[k][i];
                for (int j = 0; j < n; ++j) {
                    a_copy[k][j] -= factor * a_copy[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    return Matrix(inv);
}

// Реализация метода решения СЛАУ методом Гаусса
vector<double> Matrix::solveGauss(const vector<double>& b) const {
    vector<vector<double>> a_copy = a;  // Копия матрицы
    vector<double> b_copy = b;  // Копия правой части

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента для выбора главного элемента
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(a_copy[k][i]) > abs(a_copy[max_row][i])) {
                max_row = k;
            }
        }

        // Меняем строки местами в матрице и векторах
        swap(a_copy[i], a_copy[max_row]);
        swap(b_copy[i], b_copy[max_row]);

        // Нормализуем строку
        double diag_elem = a_copy[i][i];
        for (int j = i; j < n; ++j) {
            a_copy[i][j] /= diag_elem;
        }
        b_copy[i] /= diag_elem;

        // Обнуляем элементы ниже главного
        for (int k = i + 1; k < n; ++k) {
            double factor = a_copy[k][i];
            for (int j = i; j < n; ++j) {
                a_copy[k][j] -= factor * a_copy[i][j];
            }
            b_copy[k] -= factor * b_copy[i];
        }
    }
    // Обратный ход метода Гаусса
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b_copy[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= a_copy[i][j] * x[j];
        }
    }
    return x;
}

// Функция для нахождения определителя методом Гаусса
double Matrix::determinant() const {
    vector<vector<double>> a_copy = a;
    double det = 1;
    int sign = 1;

    for (int i = 0; i < n; ++i) {
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(a_copy[k][i]) > abs(a_copy[max_row][i])) {
                max_row = k;
            }
        }

        if (i != max_row) {
            swap(a_copy[i], a_copy[max_row]);
            sign *= -1;  // Меняем знак определителя при перестановке строк
        }

        det *= a_copy[i][i];  // Диагональные элементы для определителя

        // Приведение к треугольной форме
        for (int k = i + 1; k < n; ++k) {
            double factor = a_copy[k][i] / a_copy[i][i];
            for (int j = i; j < n; ++j) {
                a_copy[k][j] -= factor * a_copy[i][j];
            }
        }
    }

    return det * sign;
}

// Функция для нахождения LU-разложения
void Matrix::LU_decomposition(Matrix& L, Matrix& U) const {
    vector<vector<double>> L_data(n, vector<double>(n, 0.0));
    vector<vector<double>> U_data = a;

    for (int i = 0; i < n; ++i) {
        L_data[i][i] = 1.0;  // Диагональные элементы L равны 1

        for (int j = i; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < i; ++k) {
                sum += L_data[i][k] * U_data[k][j];
            }
            U_data[i][j] -= sum;
        }

        for (int j = i + 1; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < i; ++k) {
                sum += L_data[j][k] * U_data[k][i];
            }
            L_data[j][i] = (a[j][i] - sum) / U_data[i][i];
        }
    }

    L = Matrix(L_data);
    U = Matrix(U_data);
}

// Функция для решения СЛАУ методом LU-разложения
vector<double> Matrix::solveLU(const vector<double>& b) const {
    Matrix L(n, n), U(n, n);
    LU_decomposition(L, U);

    // Решаем L * y = b методом подстановки вперед
    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L.a[i][j] * y[j];
        }
    }

    // Решаем U * x = y методом подстановки назад
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U.a[i][j] * x[j];
        }
        x[i] /= U.a[i][i];
    }

    return x;
}

// Функция для нахождения определителя методом LU-разложения
double Matrix::determinantLU() const {
    Matrix L(n, n), U(n, n);
    LU_decomposition(L, U);

    double det = 1.0;
    for (int i = 0; i < n; ++i) {
        det *= U.a[i][i];
    }
    return det;
}


// Функция для оценки погрешности правой части после решения СЛАУ
double Matrix::estimateError(const std::vector<double>& b, const std::vector<double>& x) const {
    std::vector<double> r(n, 0.0);  // Вектор результата умножения A * x

    // Вычисляем r = A * x
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            r[i] += a[i][j] * x[j];
        }
    }

    // Вычисляем вектор погрешности: error = b - r
    std::vector<double> error(n);
    for (int i = 0; i < n; ++i) {
        error[i] = b[i] - r[i];
    }

    // Вычисляем Евклидову норму погрешности: ||error||_2
    double norm = 0.0;
    for (int i = 0; i < n; ++i) {
        norm += error[i] * error[i];
    }

    return std::sqrt(norm);  // Возвращаем корень из суммы квадратов
}
