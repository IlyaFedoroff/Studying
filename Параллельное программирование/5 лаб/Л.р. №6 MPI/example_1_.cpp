/*
 * Пример 1
 * Рассылка строк массива с использованием функции MPI_Scatter
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;


int main(int argc, char** argv)
{
    int N = 8;

    if (argc == 2) {
        N = atoi(argv[1]);
    }

    srand(time(NULL));
    int size, rank, sendcount, recvcount, source;
    int* sendbuf;
    int counter = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size) {
        if (rank == 0) printf("Not good value of strings\n");
        MPI_Finalize();
        return 0;
    }


    sendbuf = new int[N * N];

    printf("\n Elememts of sendbuf %d\n", sendbuf);
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {
            sendbuf[i * N + j] = rand() % 10;
            if (rank == 0) printf("%d ", sendbuf[i * N + j]);
        }
        if (rank == 0) printf("\n");
    }


    MPI_Barrier(MPI_COMM_WORLD);

  
    int* recvbuf = new int[N / size * N];

    source = 0;

    MPI_Scatter(sendbuf, N / size * N, MPI_INT, recvbuf, N / size * N, MPI_INT, source, MPI_COMM_WORLD);

    int* buff = new int[N];
    printf("\n Elememts of rank %d\n",rank);
    for (int i = 0; i < N / size; i++)
    {

        for (int j = 0; j < N; j++)
        {
            printf(" %d", recvbuf[i * N + j]);
        }


        printf("\n");
    }


    MPI_Finalize();

    delete[] sendbuf;
    delete[] recvbuf;
}
