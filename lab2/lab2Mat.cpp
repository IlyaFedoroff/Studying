#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // ������ �������� ������� A
    vector<vector<double>> a = {
        {8, 11, -1, -0.07},
        {4.056, 0.3, -5.3, 0.11},
        {0.2, 5.77, 2.8, -15},
        {12, -3.8, 1, 3}
    };

    // ������ ������ ������ ����� b
    vector<double> b = { 0.654, -24.016, 54.567, -64.78 };

    // ������� ������ ������ Matrix
    Matrix matrix(a);

    // ������� �������� �������
    cout << "�������� ������� A:" << endl;
    matrix.printMatrix();

    // ������� ���� ������� ������
    vector<double> solution = matrix.solveGauss(b);

    // ������� �������
    cout << "������� ����:" << endl;
    for (int i = 0; i < solution.size(); ++i) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }

    // ������ ����������� ������ �����
    double error = matrix.estimateError(b, solution);
    cout << "����������� ������ �����: " << error << endl;

    // �������� �������
    cout << "�������� ������� A-1: " << endl;
    Matrix reverseMatrix = matrix.inverse();
    reverseMatrix.printMatrix();

    // ���������� ������������ ������� ������
    double det_gauss = matrix.determinant();
    cout << "������������ ������� (����� ������): " << det_gauss << endl;

    // ���������� ������������ ������� LU-����������
    double det_lu = matrix.determinantLU();
    cout << "������������ ������� (����� LU): " << det_lu << endl;

    // ������� ���� ������� LU-����������
    vector<double> solutionLU = matrix.solveLU(b);
    cout << "������� ���� ������� LU-����������:" << endl;
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
//// ������� ��� ������ �������
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
//// ������� ��� ������ �������
//void printMatrix(const vector<vector<double>>& matrix, const vector<double>& b) {
//	int n = matrix.size();
//	int width = 10;  // ������ ������ ��� ������� �����
//
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			// ������� ������ ������� � ������������� ������� � 3 ������� ����� �������
//			cout << setw(width) << fixed << setprecision(3) << matrix[i][j] << " ";
//		}
//		// ������� �������� ������� b � ����� ������ ������ �������
//		cout << "| " << setw(width) << fixed << setprecision(3) << b[i] << endl;
//	}
//	cout << endl;
//}
//
//// ����� ������ ��� ������� ����
//vector<double> gauss(vector<vector<double>> a, vector<double> b) {
//	int n = a.size();
//
//	// ������ ��� (���������� � ����������� �������)
//	for (int i = 0; i < n; ++i) {
//		// ����� ������������� �������� ��� ������ �������� ��������
//		int max_row = i;
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//
//		// ������ ������ �������
//		swap(a[i], a[max_row]);
//		swap(b[i], b[max_row]);
//
//		// ��������� ������
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
//	// �������� ��� (���������� �������)
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
////����� ������ ��� ���������� ������������ � �������� �������
//double gaussJordanInverse(vector<vector<double>>& a, vector<vector<double>>& inv) {
//	int n = a.size();
//	double det = 1;
//	int sign = 1;  // ���������� ��� ������������ ������������ �����
//
//	// ������ ��� (���������� � ������������ ���� � �������� �������� �������)
//	for (int i = 0; i < n; ++i) {
//		int max_row = i;
//
//		// ����� ������������� �������� ��� ������ �������� ��������
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//
//		// ������ ������ ������� � � ������� a, � � ��������� ������� inv
//		if (i != max_row) {
//			swap(a[i], a[max_row]);
//			swap(inv[i], inv[max_row]);
//			sign = -sign;  // ������ ���� ������������ ��� ������������ �����
//		}
//
//		// ���� ������� �� ��������� �������, �� ������������ ����� 0
//		if (a[i][i] == 0) {
//			return 0;
//		}
//
//		// ����������� ������, ����� ��� ������ �� a[i][i]
//		double diag_element = a[i][i];
//		det *= diag_element;  // �������� ������������ ������� �� ������������
//		for (int j = 0; j < n; ++j) {
//			a[i][j] /= diag_element;
//			inv[i][j] /= diag_element;
//		}
//
//		// ���������� ��������� �����
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
//	// ���������� ������������ � ������ ����� ������������
//	return det * sign;
//}
//
//
////// ������� ��� ���������� �������� ������� ������� ������
////vector<vector<double>> inverseMatrix(vector<vector<double>> a) {
////	int n = a.size();
////	vector<vector<double>> inv(n, vector<double>(n, 0));
////
////	// ������� ����������� ������� [A|I]
////	for (int i = 0; i < n; ++i) {
////		inv[i][i] = 1.0;  // ��������� �������
////	}
////
////	// ������ ��� ������ ������
////	for (int i = 0; i < n; ++i) {
////		// ����� ������������� �������� ��� ������ �������� ��������
////		int max_row = i;
////		for (int k = i + 1; k < n; ++k) {
////			if (abs(a[k][i]) > abs(a[max_row][i])) {
////				max_row = k;
////			}
////		}
////
////		// ������ ������ ������� � ����� �������� (A � ��������� �����)
////		swap(a[i], a[max_row]);
////		swap(inv[i], inv[max_row]);
////
////		// ����������� ������, ����� ������� ������� ������ 1
////		double diag_elem = a[i][i];
////		for (int j = 0; j < n; ++j) {
////			a[i][j] /= diag_elem;
////			inv[i][j] /= diag_elem;
////		}
////
////		// ��������� ��������� ���� � ���� �������� ��������
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
//	// ������ ��� (���������� � ����������� �������)
//	for (int i = 0; i < n; ++i) {
//		// ����� ������������� �������� ��� ������ �������� ��������
//		int max_row = i;
//		for (int k = i + 1; k < n; ++k) {
//			if (abs(a[k][i]) > abs(a[max_row][i])) {
//				max_row = k;
//			}
//		}
//		//printMatrix(a, b);
//		// ������ ������ �������
//		swap(a[i], a[max_row]);
//		swap(b[i], b[max_row]);
//		//printMatrix(a, b);
//		// ��������� ������
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
//// ������� ��� ���������� �������
//vector<double> calculateResidual(const vector<vector<double>>& a, const vector<double>& b, const vector<double>& x) {
//	int n = a.size();
//	vector<double> residual(n);
//
//	// ������������� ������ �����
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
//	//cout << "������� ����������� ������� ���������: ";
//	//cin >> n;
//
//	//  ����������� �������
//	//vector<vector<double>> a(n, vector<double>(n)); // �������� �������
//	//vector<double> b(n);    // ��������������
//
//	
//
//	int n = 4;
//
//
//	vector<vector<double>> inv(n, vector<double>(n, 1));
//
//	// ������ �������� ������� A
//	vector<vector<double>> a = {
//		{8, 11, -1, -0.07},
//		{4.056, 0.3, -5.3, 0.11},
//		{0.2, 5.77, 2.8, -15},
//		{12, -3.8, 1, 3}
//	};
//
//	// ������ ������ ������ ����� b
//	vector<double> b = { 0.654, -24.016, 54.567, -64.78 };
//
//
//
//
//	/*cout << "������� ������������ ������� A � ������ b:" << endl;
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			cin >> a[i][j];
//		}
//		cout << "b: "; cin >> b[i];
//	}*/
//
//	cout << "\n�������� ������� ���������: " << endl;
//	printMatrix(a, b);
//
//	//vector<double> result = gauss(a, b);
//
//
//
//	double det = gaussJordanInverse(a, inv);
//
//	if (det == 0) {
//		cout << "������� ���������, �������� ������� �� ����������." << endl;
//	}
//	else {
//		cout << "������������ ������� A: " << det << endl;
//		cout << "\n�������� ������� A^-1:" << endl;
//		printMatrix(inv);
//	}
//
//
//
//
//	/*double det = gaussJordanInverse(a, inv);
//
//	if (det == 0) {
//		cout << "������� ���������, �������� ������� �� ����������." << endl;
//	}
//	else {
//		cout << "������������ ������� A: " << det << endl;
//
//	}*/
//
//	// ���������� �������� �������
//	vector<vector<double>> inverse = inverseMatrix(a);
//
//	// ����� �������� �������
//	cout << "�������� ������� A^(-1):" << endl;
//	printMatrix(inverse);
//
//	//cout << "\n������� �������: " << endl;
//	//for (int i = 0; i < n; ++i) {
//	//    cout << "x" << i + 1 << " = " << result[i] << endl;
//	//}
//
//	// ��������� �������
//	/*vector<double> residual = calculateResidual(a, b, result);
//
//	cout << "\n������� (����������� �� ������ �����): " << endl;
//	for (int i = 0; i < n; ++i) {
//		cout << "r" << i + 1 << " = " << residual[i] << endl;
//	}*/
//
//	return 0;
//}
