//#include <stdio.h>
//#include <time.h>
//#include <omp.h>
//
//long long num_steps = 1000000000;
//double step;
//
//int main(int argc, char* argv[])
//{
//    clock_t start, stop;
//    double x, pi, sum = 0.0;
//    int i;
//    step = 1.0 / (double)num_steps;
//    start = clock();
//
//#pragma omp parallel
//    {
//        double sum_local = 0.0; // ������� ���������� ��� ������ ����
//#pragma omp for
//        for (i = 0; i < num_steps; i++)
//        {
//            x = (i + 0.5) * step;
//            sum_local += 4.0 / (1.0 + x * x);
//        }
//
//#pragma omp critical
//        {
//            sum += sum_local; // �������� ������� ���� � ����� ����������
//        }
//    }
//
//    pi = sum * step;
//    stop = clock();
//
//    printf("The value of PI is %15.12f\n", pi);
//    printf("The time to calculate PI was %f seconds\n", ((double)(stop - start) / 1000.0));
//    return 0;
//}
