//
//// CONSISTENT VERSION
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <omp.h>
//#define BLOCK_SIZE 500
//int main() {
//    unsigned int iter = 200000000;  // количество итераций
//    int i, j;
//    double x, y;
//    double dUnderCurve = 0.0;
//    double pi = 0.0;
//    double r[BLOCK_SIZE * 2];   //   массив случайных чисел
//    double end_time, start_time;
//
//    srand(time(NULL));  // Инициализация генератора случайных чисел
//
//    // заполняем массив случаными числами
//    for (i = 0; i < BLOCK_SIZE * 2; i++)
//    {
//        r[i] = (float)(rand() % 100) / 100.0;
//    }
//
//    start_time = clock();
//
//    // основной цикл программы
//    for (j = 0; j < iter / BLOCK_SIZE; j++) {
//        for (i = 0; i < BLOCK_SIZE; i++) {
//            x = r[i];
//            y = r[i + BLOCK_SIZE];
//            if (x * x + y * y <= 1.0) {
//                dUnderCurve++;
//            }
//        }
//    }
//
//    pi = dUnderCurve / (double)iter * 4;
//    
//    end_time = clock();
//
//
//    printf("pi = %10.9f\n", pi);
//    printf("Seconds = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//    return 0;
//}





//// PARALLEL VERSION
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <omp.h>
//
//#define BLOCK_SIZE 500
//
//int main() {
//    unsigned int iter = 200000000;
//    int i, j;
//    double x, y;
//    double dUnderCurve = 0.0;
//    double pi = 0.0;
//    double r[BLOCK_SIZE * 2];
//    double end_time, start_time;
//
//    srand(time(NULL));  // Инициализация генератора случайных чисел
//
//    // Генерация случайных чисел
//    for (i = 0; i < BLOCK_SIZE * 2; i++) {
//        r[i] = (float)(rand() % 100) / 100.0;
//    }
//
//    start_time = clock();
//
//    // Параллельный регион
//#pragma omp parallel private(i, x, y) shared(r) reduction(+:dUnderCurve)
//    {
//#pragma omp for
//        for (j = 0; j < iter / BLOCK_SIZE; j++) {
//            for (i = 0; i < BLOCK_SIZE; i++) {
//                x = r[i];
//                y = r[i + BLOCK_SIZE];
//                if (x * x + y * y <= 1.0) {
//                    dUnderCurve++;
//                }
//            }
//        }
//    }
//
//    pi = dUnderCurve / (double)iter * 4;
//
//    end_time = clock();
//    printf("pi = %10.9f\n", pi);
//    printf("Seconds = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//
//    return 0;
//}





//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <omp.h>
//
//#define BLOCK_SIZE 500
//
//int main() {
//    unsigned int iter = 200000000;
//    int i, j;
//    double x, y;
//    double dUnderCurve = 0.0;
//    double pi = 0.0;
//    double r[BLOCK_SIZE * 2];
//    double end_time, start_time;
//
//    srand(time(NULL));  // Инициализация генератора случайных чисел
//
//    // Генерация случайных чисел
//    for (i = 0; i < BLOCK_SIZE * 2; i++) {
//        r[i] = (float)(rand() % 100) / 100.0;
//    }
//
//    start_time = clock();
//
//    // Параллельный регион
//#pragma omp parallel private(i, x, y) shared(r, dUnderCurve)
//    {
//#pragma omp for
//        for (j = 0; j < iter / BLOCK_SIZE; j++) {
//            for (i = 0; i < BLOCK_SIZE; i++) {
//                x = r[i];
//                y = r[i + BLOCK_SIZE];
//                if (x * x + y * y <= 1.0) {
//                    // Критическая секция для защиты доступа к dUnderCurve
//#pragma omp critical
//                    {
//                        dUnderCurve++;
//                    }
//                }
//            }
//        }
//    }
//
//    pi = dUnderCurve / (double)iter * 4;
//
//    end_time = clock();
//    printf("pi = %10.9f\n", pi);
//    printf("Seconds = %10.9f\n", (double)((end_time - start_time) / 1000.0));
//
//    return 0;
//}