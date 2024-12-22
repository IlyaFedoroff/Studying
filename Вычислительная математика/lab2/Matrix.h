#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
public:
    // ����������� ��� ������������� �������
    Matrix(const std::vector<std::vector<double>>& mat);

    Matrix(int n, double initialValue = 0.0);  // ����������� ��� �������� ������� ������� n x n

    // ������� ��� ������ �������
    void printMatrix() const;
    void printMatrix(const std::vector<double>& b) const;

    // ������� ��� ���������� �������� ������� ������� ������
    Matrix inverse() const;

    // ������� ��� ������� ���� ������� ������
    std::vector<double> solveGauss(const std::vector<double>& b) const;

    // ������� ��� ���������� ������������ ������� ������� ������
    double determinant() const;

    // ������� ��� ���������� LU-���������� �������
    void LU_decomposition(Matrix& L, Matrix& U) const;

    // ������� ��� ������� ���� ������� LU-����������
    std::vector<double> solveLU(const std::vector<double>& b) const;

    // ������� ��� ���������� ������������ ������� LU-����������
    double determinantLU() const;

    // ������� ��� ������ ����������� ������ ����� ����� ������� ����
    double estimateError(const std::vector<double>& b, const std::vector<double>& x) const;


private:
    std::vector<std::vector<double>> a;  // �������
    int n;                               // ����������� �������
};

#endif // MATRIX_H
