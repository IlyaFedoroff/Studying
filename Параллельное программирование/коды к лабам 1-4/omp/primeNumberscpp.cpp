//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//#include <omp.h>
//
///**
// * ������: ���������� ������� �����.
// * ---
// * ��������� ��������� ����������� �������� ���������� ������� �����
// * � ������������ ������������� ��������� ����� �����.
// * ������ ������������� ������� ����� (������ ����� �� ���������������)
// * ������� �� ��� ����� �����, ������� ��� ������ ����������� ����� �� ����� �����.
// * ���� ��������������� ����� ������� �� �����-���� �� ����������� ������������� ��� �������,
// * ��� �������� ���������; � ���� ������ ����� �������� �������.
//*/
//
//int main(int argc, char* argv[]) // ���������, ��� main ���������� int
//{
//    int i, j, limit;
//    int start, end;
//    int number_of_primes = 0;
//    int number_of_41primes = 0; /* ���������� ��������� ������� ����� ���� 4n+1 */
//    int number_of_43primes = 0; /* ���������� ��������� ������� ����� ���� 4n-1 */
//    int prime; /* ����� �������? */
//    double global_start_time, global_end_time;
//
//    // ����������� ��������� ������
//    start = 100;
//    end = 1000000000;
//
//    if (!(start % 2)) start++; // ������ � ������� ��������� �����
//
//    printf("Range to check for Primes: %d - %d\n\n", start, end);
//
//    global_start_time = omp_get_wtime(); // �������� ����� ����� ������ ���������
//
//#pragma omp parallel private(limit, j, prime)
//    {
//        double thread_start_time, thread_end_time; // ����� ������ ������ ����
//        thread_start_time = omp_get_wtime(); // �������� ����� ������ ������ ������ ����
//
//#pragma omp for
//        for (i = start; i <= end; i += 2) {
//
//            limit = (int)sqrt((float)i) + 1;
//            prime = 1; /* ������ ����� - ������� */
//            j = 3;
//            while (prime && (j <= limit)) {
//                if (i % j == 0) prime = 0;
//                j += 2;
//            }
//
//            if (prime) {
//#pragma omp critical
//                {
//                    number_of_primes++;
//                    if (i % 4 == 1) number_of_41primes++;
//                    if (i % 4 == 3) number_of_43primes++;
//                }
//            }
//        }
//
//        thread_end_time = omp_get_wtime(); // �������� ����� ���������� ������ ������ ����
//        printf("Thread %d work time = %10.9f seconds\n", omp_get_thread_num(), thread_end_time - thread_start_time);
//    }
//
//    global_end_time = omp_get_wtime(); // �������� ����� ����� ���������� ���������
//
//    printf("\nTotal work time = %10.9f seconds\n", global_end_time - global_start_time);
//    printf("\nProgram Done.\n%d primes found\n", number_of_primes);
//    printf("Number of 4n+1 primes found: %d\n", number_of_41primes);
//    printf("Number of 4n-1 primes found: %d\n", number_of_43primes);
//
//    return 0; // ���������� 0 ��� ��� ���������� ���������
//}

//
//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//#include <omp.h>
//
///**
// * ������: ���������� ������� �����.
// * ��������� ��������� ����������� �������� ���������� ������� �����
// * � ������������ ������������� ��������� ����� �����.
//*/
//
//int main(int argc, char* argv[]) {
//	int i, j, limit;
//	int start, end;
//	int number_of_primes = 0;
//	int number_of_41primes = 0;  /* ���������� �������� ������� ����� ���� 4n+1 */
//	int number_of_43primes = 0;  /* ���������� �������� ������� ����� ���� 4n-1 */
//	int prime;  /* ����� �������? */
//	double end_time, start_time;
//
//	// ����������� ��������� ������
//	start = 1;
//	end = 10000000;
//
//	if (!(start % 2)) start++;  // ����� � ��������� �����
//
//	printf("Range to check for Primes: %d - %d\n\n", start, end);
//	start_time = clock();
//
//	// ������������ ������ � �������������� ������������� ������������� �����
//#pragma omp parallel private(limit, j, prime) shared(number_of_primes, number_of_41primes, number_of_43primes)
//	{
//#pragma omp for schedule(dynamic, 100)  // ������������ ������������� � ������ �� 100 ��������
//		for (i = start; i <= end; i += 2) {
//			limit = (int)sqrt((float)i) + 1;
//			prime = 1;  // ������������, ��� ����� �������
//			j = 3;
//
//			// �������� �� �������� �����
//			while (prime && (j <= limit)) {
//				if (i % j == 0) prime = 0;
//				j += 2;
//			}
//
//			if (prime) {
//				// ������ ����� ���������� � �������������� ��������� ��������
//#pragma omp atomic
//				number_of_primes++;
//
//#pragma omp critical
//				{
//					if (i % 4 == 1) number_of_41primes++;
//				}
//
//#pragma omp critical
//				{
//					if (i % 4 == 3) number_of_43primes++;
//				}
//			}
//		}
//		
//	}
//	end_time = clock();
//	printf("Total work time = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//	printf("\nProgram Done.\n%d primes found\n", number_of_primes);
//	printf("Number of 4n+1 primes found: %d\n", number_of_41primes);
//	printf("Number of 4n-1 primes found: %d\n", number_of_43primes);
//
//	return 0;
//}
