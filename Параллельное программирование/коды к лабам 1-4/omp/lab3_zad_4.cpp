//#include <stdio.h>
//#include <stdlib.h>
//#include <omp.h>
//#include <ctime>
//
//#define n 200  // ������ ������
//
//int main() {
//    int i, j, k;
//    double a[n][n], b[n][n], c[n][n];
//    double start_time, end_time;
//
//    // ������������� ������ a � b ���������� ����������
//    for (i = 0; i < n; i++) {
//        for (j = 0; j < n; j++) {
//            a[i][j] = rand() % 100;
//            b[i][j] = rand() % 100;
//            c[i][j] = 0.0;
//        }
//    }
//
//    start_time = clock();  // ������ �������
//
//    // ������������ ��������� ������
//#pragma omp parallel for private(i, j, k) shared(a, b, c)
//    for (i = 0; i < n; i++) {
//        for (j = 0; j < n; j++) {
//            for (k = 0; k < n; k++) {
//                c[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
//
//    end_time = clock();  // ��������� �������
//
//    printf("total work time = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//
//    return 0;
//}
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <omp.h>
//#include <ctime>
//
//#define n 200  // ������ ������
//
//int main() {
//    int i, j, k;
//    double a[n][n], b[n][n], c[n][n];
//    double start_time, end_time;
//
//    // ������������� ������ a � b ���������� ����������
//    for (i = 0; i < n; i++) {
//        for (j = 0; j < n; j++) {
//            a[i][j] = rand() % 100;
//            b[i][j] = rand() % 100;
//            c[i][j] = 0.0;
//        }
//    }
//
//    start_time = clock();  // ������ �������
//
//    for (i = 0; i < n; i++) {
//        for (j = 0; j < n; j++) {
//            for (k = 0; k < n; k++) {
//                c[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
//
//    end_time = clock();  // ��������� �������
//
//    printf("total work time = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//
//    return 0;
//}
