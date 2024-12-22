///*
// * Пример 1
// * Рассылка строк массива с использованием функции MPI_Scatter
// */
//
//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <cmath>
//using namespace std;
//
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
//    int size, rank, sendcount, recvcount, source;
//    int* sendbuf;
//    int counter = 0;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (N % size) {
//        if (rank == 0) printf("Not good value of strings\n");
//        MPI_Finalize();
//        return 0;
//    }
//
//
//    sendbuf = new int[N * N];
//    int broadcast_data[6];
//
//    printf("\n Elememts of sendbuf %d\n", sendbuf);
//    for (int i = 0; i < N; i++) {
//
//        for (int j = 0; j < N; j++) {
//            sendbuf[i * N + j] = rand() % 10;
//            if (rank == 0) printf("%d ", sendbuf[i * N + j]);
//        }
//        if (rank == 0) printf("\n");
//
//        // копирование первых 6 элементов в массив для передачи
//        for (int i = 0; i < 6; i++) {
//            broadcast_data[i] = sendbuf[i];
//        }
//    }
//
//    // каждый процесс получает  от нулевого процесса по 6 элементов
//    MPI_Bcast(sendbuf, 6, MPI_INT, 0, MPI_COMM_WORLD);
//
//
//    // каждый процесс выводит полученные данные
//    printf("I am %d process. I received elements: ", rank);
//    for (int i = 0; i < 6; i++) {
//        printf("%d", broadcast_data[i]);
//    }
//    printf("\n");
//
//    MPI_Finalize();
//
//    if (rank == 0) {
//        delete[] sendbuf;
//    }
//
//    return 0;
//}
