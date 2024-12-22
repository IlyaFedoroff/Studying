//#include <iostream>
//#include <vector>
//#include <omp.h>
//
//using namespace std;
//
//
//// 1	����� ������������ ��������� ������ ������ ��������� �������
//// ������� ������������� ����� � �������������� ��������� omp for � ����������� ��������
//// ������ ����� �������� K = (N-1)/P - 1
//// MyProc - ����� �������� ���������� 
//// ibeg - MyProc * k - ������ ����� �������� ���������� 
//// iend - (MyProc + 1) * k-1 - ����� ����� ������� ���������� 
//// ���� �� ��������� ��������
//// if (ibeg > N)
////      iend = ibeg - 1;
//// else
//// ���� ��������� ������ ��������
//// if (end > N)
////      for (i = ibeg; i<=iend; i++)
////              a(i) = a(i) + b(i)
//// � ����� �������� ���������� � 1. ���� � 0, �� ������� ������� ��������
//
//
//
//// ������� � omp for
//void block1(vector<vector<int>> matrix) {
//	int n = matrix.size();       // ����� ����� � �������
//	int m = matrix[0].size();     // ����� �������� � �������
//	vector<int> products(n, 1);   // ������ ��� �������� ������������ �����
//
//	double start_time = omp_get_wtime();
//
//	//��������� #pragma omp for schedule(static): ������������ ��� ��������������� ���������� �������� ����� �������� � ������� ��������������. 
//	//�������� static ������������ �������� �� ������, ������ ����� �������� �������� ���������� ���������� �����.
//#pragma omp parallel shared(matrix, products)
//	{
//#pragma omp for schedule(static)
//		for (int i = 0; i < n; i++) {
//			products[i] = 1;  // ��������� �������� ��� ������������ ������
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "������� ������������� � omp for, �����: " << end_time - start_time << " ���." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "������������ ������ " << i << ": " << products[i] << endl;
//	}
//}
//
//
//
//// ������� ��� omp for
//void block2(vector<vector<int>> matrix) {
//
//	int n = matrix.size();       // ����� ����� � �������
//	int m = matrix[0].size();     // ����� �������� � �������
//	vector<int> products(n, 1);   // ������ ��� �������� ������������ �����
//
//	int num_threads;              // ����� �������, ������������ ��� ������� �����
//	double start_time = omp_get_wtime();
//
//#pragma omp parallel shared(matrix, products, num_threads)
//	{
//		int thread_id = omp_get_thread_num();     // ����� �������� ������
//#pragma omp single
//		{
//			num_threads = omp_get_num_threads();  // ���������� ���������� ������� ���� ���
//		}
//
//		int k = (n + num_threads - 1) / num_threads;  // ������ ����� ��������
//		int ibeg = thread_id * k;                     // ������ �����
//		int iend = (thread_id + 1) * k - 1;           // ����� �����
//
//		// �������� �� ������, ���� �� ��������� ��������
//		if (ibeg >= n) {
//			iend = ibeg - 1;
//		}
//		else if (iend >= n) {
//			// ���� ��������� ������ ��������
//			iend = n - 1;
//		}
//
//		for (int i = ibeg; i <= iend; i++) {
//			products[i] = 1;  // ��������� �������� ��� ������������ ������
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "������� ������������� � omp for, �����: " << end_time - start_time << " ���." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "������������ ������ " << i << ": " << products[i] << endl;
//	}
//}
//
//
//// ����������� ������������� ��������
//// for (i = MyProc; i < N; i+=P)
////      a[i] = a[i] + b[i]
//// � ����� �������� ���������� � 1. ���� � 0, �� ������� ������� ��������
//
//// ����������� � omp for
////��������� #pragma omp for schedule(static, 1) : ���������� ����������� ������������� � �������� ����� ������ 1. 
//// ��� ��������, ��� ������ ����� �������� ���� �������� �� ���, ��� �������� � ������������ ������������� ����� ����� ��������.
////����������� ������������� : ������ ����� ������������ ��� ��������� �����, ��� ������������ ����������� ������������� ��������,
//// ���� ������ ����� ������ ������ ������ ��� ��������� ���������.
//void for1(vector<vector<int>> matrix) {
//	int n = matrix.size();       // ����� ����� � �������
//	int m = matrix[0].size();     // ����� �������� � �������
//	vector<int> products(n, 1);   // ������ ��� �������� ������������ �����
//
//	double start_time = omp_get_wtime();
//
//#pragma omp parallel shared(matrix, products)
//	{
//#pragma omp for schedule(static, 1)
//		for (int i = 0; i < n; i++) {
//			products[i] = 1;  // ��������� �������� ��� ������������ ������
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	cout << "����������� ������������� � omp for, �����: " << end_time - start_time << " ���." << endl;
//
//	for (int i = 0; i < n; i++) {
//		cout << "������������ ������ " << i << ": " << products[i] << endl;
//	}
//}
//
//// ����������� ��� omp for
//void for2(vector<vector<int>> matrix) {
//	int n = matrix.size();  // ���������� ����� � �������
//	int m = matrix[0].size();  // ���������� �������� � �������
//	std::vector<int> products(n, 1);  // ������ ��� �������� ������������ �����
//
//	double start_time = omp_get_wtime();  // ������ ������ �������
//
//#pragma omp parallel
//	{
//		int MyProc = omp_get_thread_num();  // ����� �������� ������
//		int P = omp_get_num_threads();  // ����� ���������� �������
//
//		for (int i = MyProc; i < n; i += P) {
//			products[i] = 1;  // ������������� ������������ ��� ������ i
//			for (int j = 0; j < m; j++) {
//				products[i] *= matrix[i][j];  // ���������� ������������ ��������� ������
//			}
//		}
//	}
//
//	double end_time = omp_get_wtime();  // ����� ������ �������
//	std::cout << "����������� ������������� ��� omp for, �����: " << end_time - start_time << " ���." << std::endl;
//
//	// ����� �����������
//	for (int i = 0; i < n; i++) {
//		std::cout << "������������ ������ " << i << ": " << products[i] << std::endl;
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