#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // Задаем основную матрицу A
    vector<vector<double>> a = {
        {8, 11, -1, -0.07},
        {4.056, 0.3, -5.3, 0.11},
        {0.2, 5.77, 2.8, -15},
        {12, -3.8, 1, 3}
    };

    // Задаем вектор правой части b
    vector<double> b = { 0.654, -24.016, 54.567, -64.78 };

    // Создаем объект класса Matrix
    Matrix matrix(a);

    // Выводим исходную матрицу
    cout << "Исходная матрица A:" << endl;
    matrix.printMatrix();

    // Решение СЛАУ методом Гаусса
    vector<double> solution = matrix.solveGauss(b);

    // Выводим решение
    cout << "Решение СЛАУ:" << endl;
    for (int i = 0; i < solution.size(); ++i) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }

    // Оценка погрешности правой части
    double error = matrix.estimateError(b, solution);
    cout << "Погрешность правой части: " << error << endl;

    // Обратная матрица
    cout << "Обратная матрица A-1: " << endl;
    Matrix reverseMatrix = matrix.inverse();
    reverseMatrix.printMatrix();

    // Нахождение определителя методом Гаусса
    double det_gauss = matrix.determinant();
    cout << "Определитель матрицы (метод Гаусса): " << det_gauss << endl;

    // Нахождение определителя методом LU-разложения
    double det_lu = matrix.determinantLU();
    cout << "Определитель матрицы (метод LU): " << det_lu << endl;

    // Решение СЛАУ методом LU-разложения
    vector<double> solutionLU = matrix.solveLU(b);
    cout << "Решение СЛАУ методом LU-разложения:" << endl;
    for (double x : solution) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}























//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <iomanip>
//
//using namespace std;
//
//
//
//// Функция для вывода матрицы
//void printMatrix(const vector<vector<double>>& matrix) {
//	int n = matrix.size();
//	int width = 10;
//
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < matrix[i].size(); ++j) {
//			cout << setw(width) << fixed << setprecision(3) << matrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//// Функция для вывода матрицы
//void printMatrix(const vector<vector<double>>& matrix, const vector<double>& b) {
//	int n = matrix.size();
//	int width = 10;  // Задаем ширину для каждого числа
//
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			// Выводим каждый элемент с фиксированной шириной и 3 знаками после запятой
//			cout << setw(width) << fixed << setprecision(3) << matrix[i][j] << " ";
//		}
//		// Выводим элементы вектора b в конце каждой строки матрицы
//		cout << "| " << setw(width) << fixed << setprecision(3) << b[i] << endl;
//	}
//	cout << endl;
//}
//
//// Метод Гаусса для решения СЛАУ
//vector<double> gauss(vector<vector<double>> a, vector<double> b) {
//	int n = a.size();
//
//	// Прямой ход (приведение к треугольной матрице)
//	for (int i = 0; i < n; ++i) {
//		// Поиск максимального элемента для выбора главного элемента
//		int max_row = i;
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//
//		// Меняем строки местами
//		swap(a[i], a[max_row]);
//		swap(b[i], b[max_row]);
//
//		// Обнуление строки
//		for (int k = i + 1; k < n; ++k) {
//			double factor = a[k][i] / a[i][i];
//			for (int j = i; j < n; ++j) {
//				a[k][j] -= factor * a[i][j];
//			}
//			b[k] -= factor * b[i];
//		}
//	}
//
//	//printMatrix(a, b);
//
//	// Обратный ход (нахождение решения)
//	vector<double> x(n);
//	for (int i = n - 1; i >= 0; --i) {
//		x[i] = b[i];
//		for (int j = i + 1; j < n; ++j) {
//			x[i] -= a[i][j] * x[j];
//		}
//		x[i] /= a[i][i];
//	}
//
//	return x;
//}
//
////Метод Гаусса для вычисления определителя и обратной матрицы
//double gaussJordanInverse(vector<vector<double>>& a, vector<vector<double>>& inv) {
//	int n = a.size();
//	double det = 1;
//	int sign = 1;  // переменная для отслеживания перестановок строк
//
//	// Прямой ход (приведение к треугольному виду и создание обратной матрицы)
//	for (int i = 0; i < n; ++i) {
//		int max_row = i;
//
//		// Поиск максимального элемента для выбора главного элемента
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//
//		// Меняем строки местами и в матрице a, и в единичной матрице inv
//		if (i != max_row) {
//			swap(a[i], a[max_row]);
//			swap(inv[i], inv[max_row]);
//			sign = -sign;  // Меняем знак определителя при перестановке строк
//		}
//
//		// Если элемент на диагонали нулевой, то определитель равен 0
//		if (a[i][i] == 0) {
//			return 0;
//		}
//
//		// Нормализуем строку, делим всю строку на a[i][i]
//		double diag_element = a[i][i];
//		det *= diag_element;  // Умножаем диагональный элемент на определитель
//		for (int j = 0; j < n; ++j) {
//			a[i][j] /= diag_element;
//			inv[i][j] /= diag_element;
//		}
//
//		// Приведение остальных строк
//		for (int k = 0; k < n; ++k) {
//			if (k != i) {
//				double factor = a[k][i];
//				for (int j = 0; j < n; ++j) {
//					a[k][j] -= factor * a[i][j];
//					inv[k][j] -= factor * inv[i][j];
//				}
//			}
//		}
//	}
//
//	// Возвращаем определитель с учётом знака перестановок
//	return det * sign;
//}
//
//
////// Функция для нахождения обратной матрицы методом Гаусса
////vector<vector<double>> inverseMatrix(vector<vector<double>> a) {
////	int n = a.size();
////	vector<vector<double>> inv(n, vector<double>(n, 0));
////
////	// Создаем расширенную матрицу [A|I]
////	for (int i = 0; i < n; ++i) {
////		inv[i][i] = 1.0;  // единичная матрица
////	}
////
////	// Прямой ход метода Гаусса
////	for (int i = 0; i < n; ++i) {
////		// Поиск максимального элемента для выбора главного элемента
////		int max_row = i;
////		for (int k = i + 1; k < n; ++k) {
////			if (abs(a[k][i]) > abs(a[max_row][i])) {
////				max_row = k;
////			}
////		}
////
////		// Меняем строки местами в обоих матрицах (A и единичная часть)
////		swap(a[i], a[max_row]);
////		swap(inv[i], inv[max_row]);
////
////		// Нормализуем строку, делая главный элемент равным 1
////		double diag_elem = a[i][i];
////		for (int j = 0; j < n; ++j) {
////			a[i][j] /= diag_elem;
////			inv[i][j] /= diag_elem;
////		}
////
////		// Обнуление элементов ниже и выше главного элемента
////		for (int k = 0; k < n; ++k) {
////			if (k != i) {
////				double factor = a[k][i];
////				for (int j = 0; j < n; ++j) {
////					a[k][j] -= factor * a[i][j];
////					inv[k][j] -= factor * inv[i][j];
////				}
////			}
////		}
////	}
////
////
////
////	return inv;
////}
//
//void treug(vector<vector<double>> a, vector<double> b) {
//	int n = a.size();
//
//	// Прямой ход (приведение к треугольной матрице)
//	for (int i = 0; i < n; ++i) {
//		// Поиск максимального элемента для выбора главного элемента
//		int max_row = i;
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//		//printMatrix(a, b);
//		// Меняем строки местами
//		swap(a[i], a[max_row]);
//		swap(b[i], b[max_row]);
//		//printMatrix(a, b);
//		// Обнуление строки
//		for (int k = i + 1; k < n; ++k) {
//			double factor = a[k][i] / a[i][i];
//			for (int j = i; j < n; ++j) {
//				a[k][j] -= factor * a[i][j];
//			}
//			b[k] -= factor * b[i];
//		}
//	}
//
//	printMatrix(a, b);
//}
//
//// Функция для вычисления невязки
//vector<double> calculateResidual(const vector<vector<double>>& a, const vector<double>& b, const vector<double>& x) {
//	int n = a.size();
//	vector<double> residual(n);
//
//	// Пересчитываем правую часть
//	for (int i = 0; i < n; ++i) {
//		double sum = 0;
//		for (int j = 0; j < n; ++j) {
//			sum += a[i][j] * x[j];
//		}
//		residual[i] = b[i] - sum;
//	}
//
//	return residual;
//}
//
//int main() {
//	setlocale(LC_ALL, "Russian");
//	//int n;
//	//cout << "Введите размерность системы уравнений: ";
//	//cin >> n;
//
//	//  расширенная матрица
//	//vector<vector<double>> a(n, vector<double>(n)); // основная матрица
//	//vector<double> b(n);    // дополнительная
//
//
//
//	int n = 4;
//
//
//	vector<vector<double>> inv(n, vector<double>(n, 1));
//
//	// Задаем основную матрицу A
//	vector<vector<double>> a = {
//		{8, 11, -1, -0.07},
//		{4.056, 0.3, -5.3, 0.11},
//		{0.2, 5.77, 2.8, -15},
//		{12, -3.8, 1, 3}
//	};
//
//	// Задаем вектор правой части b
//	vector<double> b = { 0.654, -24.016, 54.567, -64.78 };
//
//
//
//
//	/*cout << "Введите коэффициенты матрицы A и вектор b:" << endl;
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			cin >> a[i][j];
//		}
//		cout << "b: "; cin >> b[i];
//	}*/
//
//	cout << "\nИсходная система уравнений: " << endl;
//	printMatrix(a, b);
//
//	//vector<double> result = gauss(a, b);
//
//
//
//	double det = gaussJordanInverse(a, inv);
//
//	if (det == 0) {
//		cout << "Матрица вырождена, обратной матрицы не существует." << endl;
//	}
//	else {
//		cout << "Определитель матрицы A: " << det << endl;
//		cout << "\nОбратная матрица A^-1:" << endl;
//		printMatrix(inv);
//	}
//
//
//
//
//	/*double det = gaussJordanInverse(a, inv);
//
//	if (det == 0) {
//		cout << "Матрица вырождена, обратной матрицы не существует." << endl;
//	}
//	else {
//		cout << "Определитель матрицы A: " << det << endl;
//
//	}*/
//
//	// Нахождение обратной матрицы
//	vector<vector<double>> inverse = inverseMatrix(a);
//
//	// Вывод обратной матрицы
//	cout << "Обратная матрица A^(-1):" << endl;
//	printMatrix(inverse);
//
//	//cout << "\nРешение системы: " << endl;
//	//for (int i = 0; i < n; ++i) {
//	//    cout << "x" << i + 1 << " = " << result[i] << endl;
//	//}
//
//	// Вычисляем невязку
//	/*vector<double> residual = calculateResidual(a, b, result);
//
//	cout << "\nНевязка (погрешность по правой части): " << endl;
//	for (int i = 0; i < n; ++i) {
//		cout << "r" << i + 1 << " = " << residual[i] << endl;
//	}*/
//
//	return 0;
//}
