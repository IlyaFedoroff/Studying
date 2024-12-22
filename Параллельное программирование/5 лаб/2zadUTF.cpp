//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <cmath>
//using namespace std;
//
//int main(int argc, char** argv)
//{
//    int N = 8;
//
//    if (argc == 2) {
//        N = atoi(argv[1]);
//    }
//
//    srand(time(NULL));
//    int size, rank;
//    int* sendbuf;
//    int* gatherbuf = nullptr;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    // Проверяем, делится ли количество строк на число процессов
//    if (N % size) {
//        if (rank == 0) printf("Invalid value for N \n");
//        MPI_Finalize();
//        return 0;
//    }
//
//    // Размер строки
//    int row_size = N;
//    sendbuf = new int[N * N];
//    // Создаем матрицу только на процессе 0
//    if (rank == 0) {
//        printf("Matrix:\n");
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                sendbuf[i * N + j] = rand() % 10;
//                printf("%d ", sendbuf[i * N + j]);
//            }
//            printf("\n");
//        }
//    }
//
//    MPI_Barrier(MPI_COMM_WORLD);
//
//    // Буфер для получения одной строки на каждом процессе
//    int* recvbuf = new int[row_size];
//
//    // Рассылка строк (одной строки на процесс)
//    MPI_Scatter(sendbuf, row_size, MPI_INT, recvbuf, row_size, MPI_INT, 0, MPI_COMM_WORLD);
//
//    printf("\nProcess %d received row:\n", rank);
//    for (int i = 0; i < row_size; i++) {
//        printf("%d ", recvbuf[i]);
//    }
//    printf("\n");
//
//    // Нулевой процесс создает массив для сборки всех строк
//    if (rank == 0) {
//        gatherbuf = new int[N * N];
//    }
//
//    // Сбор строк обратно на процесс 0
//    MPI_Gather(recvbuf, row_size, MPI_INT, gatherbuf, row_size, MPI_INT, 0, MPI_COMM_WORLD);
//
//
//    //MPI_Barrier(MPI_COMM_WORLD);
//    // Вывод собранной матрицы на нулевом процессе
//    if (rank == 0) {
//        printf("\nReconstructed Matrix on process 0:\n");
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                printf("%d ", gatherbuf[i * N + j]);
//            }
//            printf("\n");
//        }
//    }
//
//    // Освобождение памяти
//    if (rank == 0) {
//        delete[] sendbuf;
//        delete[] gatherbuf;
//    }
//    delete[] recvbuf;
//
//    MPI_Finalize();
//    return 0;
//}
