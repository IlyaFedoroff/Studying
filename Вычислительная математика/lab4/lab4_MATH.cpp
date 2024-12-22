#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip> // Для форматирования вывода

using namespace std;

// метод Зейделя
vector<double> seidel(const vector<vector<double>>& A, const vector<double>& b, double epsilon, int& iterations) {
	int n = A.size();
	vector<double> x(n, 0.0), x_prev(n, 0.0);
	bool flag;

	iterations = 0;

	// основной цикл метода Зейделя
	do {
		flag = true;
		for (int i = 0; i < n; ++i) {
			
			double sum = b[i];	
			// SIGMA aij*xj
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					sum -= A[i][j] * x[j];
				}
			}
			x_prev[i] = x[i];
			x[i] = sum / A[i][i];
			
		}

		// Вывод текущих значений на каждой итерации
		cout << "Итерация " << iterations + 1 << ": ";
		for (double xi : x) {
			cout << std::setw(10) << xi << " "; // Вывод с форматированием
		}
		cout << endl;

		// Проверка на достижение заданной точности
		for (int i = 0; i < n; ++i) {
			if (fabs(x[i] - x_prev[i]) > epsilon) {
				flag = false;
				break;
			}
		}
		iterations++;
	} while (!flag);

	return x;
}

int main() {
	setlocale(LC_ALL, "rus");

	vector<vector<double>> A = {
				{12, -3.8, 1, 3},
				{ 8, 11, -1, -0.07 },
				{4.056, 0.3, -5.3, 0.11},
				{0.2, 5.77, 2.8, -15}
	};

	// Вектор правых частей
	vector<double> b = { -64.78,0.654 ,-24.016 ,54.567 };



	// Вторая матрица и вектор правых частей
	vector<vector<double>> A2 = {
		{100, -20.2, 32.7, 40.1253},
		{25.7, 322, -10.7, 36.5},
		{-1, 4.3245, 76, 3.5},
		{31.4, 222, 78.7, 455}
	};
	vector<vector<double>> A3 = {
		{-4, -1.5, 1.6, 1.4},
		{-1, 5, -1.2, -1.2},
		{1.5, -1.55, 6, -1.32},
		{1.1, 1, 1.123, 4}
	};

	vector<double> b2 = { 3.4252, 32.531, -5.451, 27.254 };

	// Точности для расчета
	vector<double> epsilons = { 1e-2, 1e-3, 1e-4, 1e-5, 1e-6 };

	cout << "Исследование сходимости метода Зейделя:\n";
	cout << "-----------------------------------------\n";

	for (double epsilon : epsilons) {
		int iterations = 0;
		vector<double> result = seidel(A, b, epsilon, iterations);

		// Вывод результатов
		cout << "Точность: " << epsilon << ", Число итераций: " << iterations << endl;
		cout << "Решение (x1, x2, x3, x4): ";
		for (double xi : result) {
			cout << std::setw(10) << xi << " ";
		}
		cout << endl << endl;
	}

	return 0;
}





















//#include <iostream>
//#include <cmath>
//#include <vector>
//
//
//using namespace std;
//
//
//// метод Зейделя
//// похож на метод простых итераций
//
//
//vector<double> seidel(const vector<vector<double>>& A, const vector<double>& b, double epsilon, int& iterations) {
//	int n = A.size();
//	vector<double> x(n, 0.0), x_prev(n, 0.0);
//	bool flag;
//
//	iterations = 0;
//
//	for (int i = 0; i < n; ++i) {
//		double sum = 0.0;
//		for (int j = 0; j < n; ++j) {
//			if (i != j) {
//				sum += fabs(A[i][j]);
//			}
//		}
//		if (fabs(A[i][i]) <= sum) {
//			std::cerr << "Ошибка: система не диагонально доминантна." << std::endl;
//			return x;
//		}
//	}
//
//
//
//	// основной цикл
//	do {
//		flag = true;
//		for (int i = 0; i < n; ++i) {
//			double sum = b[i];
//			for (int j = 0; j < n; ++j) {
//				if (i != j) {   // если не диагональный элемент
//					sum -= A[i][j] * x[j];
//				}
//			}
//			// запоминаем для предыдущего (обновляем)
//			x_prev[i] = x[i];   // Новый предыдущий 
//			x[i] = sum / A[i][i]; // по формуле считаем x итый
//		}
//		
//		// Выводим текущее значение x на каждой итерации
//		cout << "Итерация " << iterations + 1 << ": ";
//		for (double xi : x) {
//			cout << xi << " ";
//		}
//		cout << endl;
//
//		// проверяем на достаточное приближение
//		for (int i = 0; i < n; ++i) {
//			if (fabs(x[i] - x_prev[i]) > epsilon) {
//				flag = false;
//				break;
//			}
//		}
//		iterations++;
//	} while (!flag);
//
//	return x;
//}
//
//
//int main() {
//	setlocale(LC_ALL, "rus");
//	// Матрица коэффициентов
//	/*vector<vector<double>> A = {
//		{8, 11, -1, -0.07},
//		{4.056, 0.3, -5.3, 0.11},
//		{0.2, 5.77, 2.8, -15},
//		{12, -3.8, 1, 3}
//	};*/
//
//	vector<vector<double>> A = {
//		{12, -3.8, 1, 3},
//		{ 8, 11, -1, -0.07 },
//		{4.056, 0.3, -5.3, 0.11},
//		{0.2, 5.77, 2.8, -15}
//	};
//
//	// Вектор правых частей
//	vector<double> b = { -64.78,0.654 ,-24.016 ,54.567 };
//
//	vector<vector<double>> A2 = {
//    {100, -20.2, 32.7, 40.1253},
//    {25.7, 322,-10.7, 36.5},
//    {-1, 4.3245, 76, 3.5},
//    {31.4,222, 78.7, 455}
//};
//
//// Вектор правых частей
//vector<double> b2 = {3.4252,32.531, -5.451, 27.254};
//
//
//
//	// Точности для расчета
//	vector<double> epsilons = { 1e-2, 1e-3, 1e-4, 1e-5, 1e-6 };
//
//	for (double epsilon : epsilons) {
//		int iterations = 0;
//		vector<double> result = seidel(A2, b2, epsilon, iterations);
//
//		
//
//		cout << "Точность: " << epsilon << ", Итераций: " << iterations << endl;
//		cout << "Решение: ";
//		for (double xi : result) {
//			cout << xi << " ";
//		}
//		cout << endl << endl;
//	}
//
//	return 0;
//}