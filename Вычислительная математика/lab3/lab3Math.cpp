#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


void solveTridiagonalSystem(const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d, vector<double>& x, int n) {
    vector<double> alpha(n, 0.0), beta(n, 0.0);

    cout << "������ ��� ������ ��������:\n";
    // ������ ���
    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];
    cout << "alpha[0] = " << alpha[0] << "\tbeta[0] = " << beta[0] << "\n";

    for (int i = 1; i < n; i++) {
        double znam = b[i] + a[i] * alpha[i - 1];
        alpha[i] = -c[i] / znam;
        beta[i] = (d[i] - a[i] * beta[i - 1]) / znam;
        cout << "alpha[" << i << "] = " << alpha[i] << "\tbeta[" << i << "] = " << beta[i] << "\n";
    }

    cout << "\n�������� ��� ������ ��������:\n";
    // �������� ���
    x[n - 1] = beta[n - 1];
    cout << "x[" << n - 1 << "] = " << x[n - 1] << "\n";

    for (int i = n - 2; i >= 0; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
        cout << "x[" << i << "] = " << x[i] << "\n";
    }

    cout << "\n������� ������� ������� ��������:\n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << "\n";
    }
}

//void solveTridiagonalSystem(const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d, vector<double>& x, int n) {
//    vector<double> alpha(n, 0.0), beta(n, 0.0);
//
//    // ������ ���
//    alpha[0] = -c[0] / b[0];
//    beta[0] = d[0] / b[0];
//    cout << "alpha[0] = "<< alpha[0] << endl;
//    cout << "beta[0] = " << beta[0] << endl;
//    for (int i = 1; i < n; i++) {
//        double znam = b[i] + a[i] * alpha[i - 1];
//        alpha[i] = -c[i] / znam;
//        beta[i] = (d[i] - a[i] * beta[i - 1]) / znam;
//        cout << "alpha " << i << " = " << alpha[i] << endl;
//        cout << "beta " << i << " = " << beta[i] << endl;
//    }
//    
//    // �������� ���
//    x[n - 1] = beta[n - 1];
//    for (int i = n - 2; i >= 0; i--) {
//        x[i] = alpha[i] * x[i + 1] + beta[i];
//        //cout << "x[" << i << "] = " << x[i] << endl;
//    }
//}


// ���������� ����� �������
double norm(const vector<double>& vec) {
    double sum = 0.0;
    for (double val : vec) {
        sum += val * val;
    }
    return sqrt(sum);
}

// ��������� ������� �� ������
vector<double> multiplyMatrixVector(const vector<vector<double>>& A, const vector<double>& x, int n) {
    vector<double> result(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

vector<double> getMainDiag(vector<vector<double>>& A, int size) {
    vector<double> resMainDiag(size,0);
    for (int i = 0; i < size; i++) {
        resMainDiag[i] = A[i][i];
    }
    return resMainDiag;
}
vector<double> getBotDiag(vector<vector<double>>& A, int size) {
    vector<double> resBotDiag(size,0);
    for (int i = 1; i < size; i++) {
        resBotDiag[i] = A[i][i-1];
    }
    return resBotDiag;
}
vector<double> getTopDiag(vector<vector<double>>& A, int size) {
    vector<double> resTopDiag(size,0);
    for (int i = 0; i < size-1; i++) {
        resTopDiag[i] = A[i][i+1];
        //cout << "���������: " << resTopDiag[i] << endl;
    }
    return resTopDiag;
}

// ������� ��� ������ ������� � ���������
void printVector(const vector<double>& vec, const string& name) {
    cout << name << ": ";
    for (const auto& val : vec) {
        cout << val << '\t';
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int n = 5;  // ������ ������� (����� ���������)


    // ������� A 
    vector<vector<double>> A = {
        {15, -7.4, 0, 0, 0},
        {3.8, 11.304, -4.88, 0, 0},
        {0, -5.71, 32.22, -12.6, 0},
        {0, 0, 11, 29.3, 7.5},
        {0, 0, 0, 5.3, -14}
    };

    //cout <<"������� A[0][0]="<< A[0][1] << endl;

    // ������������ ���������������� �������
    vector<double> a = getBotDiag(A, 5);
    vector<double> b = getMainDiag(A, 5);
    vector<double> c = getTopDiag(A, 5);
    vector<double> d = { 19.64, 10.2496, 37.42, 156.39, -38.51 };  // ������ ������ ������
    /*for (int i = 0; i < 5; i++) {
        cout << b[i] << '\t';
    }
    cout << endl;*/

    vector<double> x(n, 0.0);  // ������ ��� �������� �������

    // ������ ������� ������� ������������ ��������
    solveTridiagonalSystem(a, b, c, d, x, n);

    // ����� �������
    cout << "������� �������:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }


    // ������� ������� (��������� ������ x)
    vector<double> xResh = { 2, 1.4, 2.7, 3.3, 4 };

    // �������� ������� d
    vector<double> d_calc = multiplyMatrixVector(A, xResh, n);
    
    // ����� �������������� ������� d
    printVector(d_calc, "������������� ������ d");

    // ���������� ��������
    vector<double> diff(n, 0.0);
    for (int i = 0; i < n; i++) {
        diff[i] = d[i] - d_calc[i];
    }

    // ����� �������� ��������
    printVector(diff, "�������� �������� d");

    // ����� ��������
    double norm_b = norm(d);
    double norm_diff = norm(diff);

    // ���������� �����������
    double error = (norm_diff / norm_b) * 100;

    // ����� ���������� � ��������� �� 8 ������ ����� �������
    cout << fixed << setprecision(20);
    //cout << "����� ��������� ������� d: " << norm_b << endl;
    //cout << "����� �������� ��������: " << norm_diff << endl;
    cout << "�����������: " << error << " %" << endl;
    cout << endl;

    return 0;
}




