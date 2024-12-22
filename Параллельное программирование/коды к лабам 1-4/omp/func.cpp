//#include <iostream>
//#include <vector>
//#include <omp.h>
//
//using namespace std;
//
//
//// 1	Найти произведения элементов каждой строки двумерной матрицы
//// блочное распределение цикла с использованием директивы omp for с применением редукции
//// размер блока итераций K = (N-1)/P - 1
//// MyProc - номер текущего процессора 
//// ibeg - MyProc * k - начало блока итераций процессора 
//// iend - (MyProc + 1) * k-1 - конец блока тераций процессора 
//// если не досталось итераций
//// if (ibeg > N)
////      iend = ibeg - 1;
//// else
//// если досталось меньше итераций
//// if (end > N)
////      for (i = ibeg; i<=iend; i++)
////              a(i) = a(i) + b(i)
//// в цикле итерации начинаются с 1. Если с 0, то формулы следует изменить
//
//
//
//// блочное с omp for
//void block1(vector<vector<int>> matrix) {
//	int n = matrix.size();       // Число строк в матрице
//	int m = matrix[0].size();     // Число столбцов в матрице
//	vector<int> products(n, 1);   // Вектор для хранения произведений строк
//
//	double start_time = omp_get_wtime();
//
//	//Директива #pragma omp for schedule(static): Используется для автоматического разделения итераций между потоками с блочным распределением. 
//	//Параметр static распределяет итерации по блокам, каждый поток получает примерно одинаковое количество строк.
//#pragma omp parallel shared(matrix, products)
//	{
//#pragma omp for schedule(static)
//		for (int i = 0; i < n; i++) {
//			products[i] = 1;  // Начальное значение для произведения строки
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "Блочное распределение с omp for, время: " << end_time - start_time << " сек." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "Произведение строки " << i << ": " << products[i] << endl;
//	}
//}
//
//
//
//// блочное без omp for
//void block2(vector<vector<int>> matrix) {
//
//	int n = matrix.size();       // Число строк в матрице
//	int m = matrix[0].size();     // Число столбцов в матрице
//	vector<int> products(n, 1);   // Вектор для хранения произведений строк
//
//	int num_threads;              // Число потоков, используется для расчета блока
//	double start_time = omp_get_wtime();
//
//#pragma omp parallel shared(matrix, products, num_threads)
//	{
//		int thread_id = omp_get_thread_num();     // Номер текущего потока
//#pragma omp single
//		{
//			num_threads = omp_get_num_threads();  // Определяем количество потоков один раз
//		}
//
//		int k = (n + num_threads - 1) / num_threads;  // Размер блока итераций
//		int ibeg = thread_id * k;                     // Начало блока
//		int iend = (thread_id + 1) * k - 1;           // Конец блока
//
//		// Проверка на случай, если не досталось итераций
//		if (ibeg >= n) {
//			iend = ibeg - 1;
//		}
//		else if (iend >= n) {
//			// Если досталось меньше итераций
//			iend = n - 1;
//		}
//
//		for (int i = ibeg; i <= iend; i++) {
//			products[i] = 1;  // Начальное значение для произведения строки
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "Блочное распределение с omp for, время: " << end_time - start_time << " сек." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "Произведение строки " << i << ": " << products[i] << endl;
//	}
//}
//
//
//// Циклическое распределение итераций
//// for (i = MyProc; i < N; i+=P)
////      a[i] = a[i] + b[i]
//// в цикле итерации начинаются с 1. Если с 0, то формулы следует изменить
//
//// циклическое с omp for
////Директива #pragma omp for schedule(static, 1) : Использует циклическое распределение с размером блока равным 1. 
//// Это означает, что каждый поток получает одну итерацию за раз, что приводит к циклическому распределению строк между потоками.
////Циклическое распределение : Потоки будут чередоваться при обработке строк, что обеспечивает равномерное распределение нагрузки,
//// если строки имеют разные объёмы данных или сложность обработки.
//void for1(vector<vector<int>> matrix) {
//	int n = matrix.size();       // Число строк в матрице
//	int m = matrix[0].size();     // Число столбцов в матрице
//	vector<int> products(n, 1);   // Вектор для хранения произведений строк
//
//	double start_time = omp_get_wtime();
//
//#pragma omp parallel shared(matrix, products)
//	{
//#pragma omp for schedule(static, 1)
//		for (int i = 0; i < n; i++) {
//			products[i] = 1;  // Начальное значение для произведения строки
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "Циклическое распределение с omp for, время: " << end_time - start_time << " сек." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "Произведение строки " << i << ": " << products[i] << endl;
//	}
//}
//
//// циклическое без omp for
//void for2(vector<vector<int>> matrix) {
//	int n = matrix.size();  // Количество строк в матрице
//	int m = matrix[0].size();  // Количество столбцов в матрице
//	std::vector<int> products(n, 1);  // Вектор для хранения произведений строк
//
//	double start_time = omp_get_wtime();  // Начало замера времени
//
//#pragma omp parallel
//	{
//		int MyProc = omp_get_thread_num();  // Номер текущего потока
//		int P = omp_get_num_threads();  // Общее количество потоков
//
//		for (int i = MyProc; i < n; i += P) {
//			products[i] = 1;  // Инициализация произведения для строки i
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];  // Вычисление произведения элементов строки
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();  // Конец замера времени
//	std::cout << "Циклическое распределение без omp for, время: " << end_time - start_time << " сек." << std::endl;
//
//	// Вывод результатов
//	for (int i = 0; i < n; i++) {
//		std::cout << "Произведение строки " << i << ": " << products[i] << std::endl;
//	}
//}
//
//
//int main() {
//	setlocale(LC_ALL, "rus");
//	vector<vector<int>> matrix = {
//		{1, 2, 3},
//		{4, 5, 6},
//		{7, 8, 9}
//	};
//
//	for2(matrix);
//
//	return 0;
//}