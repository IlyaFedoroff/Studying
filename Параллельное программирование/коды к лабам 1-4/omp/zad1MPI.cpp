//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <algorithm>  // ��� std::max
//#include <locale.h>
//using namespace std;
//
//int main(int argc, char** argv) {
//    setlocale(LC_ALL, "RU"); // RU ����������� �������
//    int N = 8;  // ������ ������� (�� ��������� 8x8)
//
//    if (argc == 2) {
//        N = atoi(argv[1]);  // ���� ������� ��������, ���������� ��� ��� ������ �������
//    }
//
//    srand(time(NULL));
//    int size, rank, sendcount, recvcount;
//    int* sendbuf = nullptr;
//
//    // ������������� MPI
//    MPI_Init(&argc, &argv); // ������ ������� 
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // �������� ���������� rank(�����) 
//    MPI_Comm_size(MPI_COMM_WORLD, &size);   // � ����� ���������� ��������� size
//
//    // ��������� ��������� ���������� ����� �� ����� ���������
//    if (N % size != 0) {
//        if (rank == 0) printf("The number of lines must be a multiple of the number of processes.\n");
//        MPI_Finalize();
//        return 0;
//    }
//
//    int rows_per_proc = N / size;  // ����� �����, �������������� ������ ���������
//
//    // ������� �������
//    if (rank == 0) {
//        // ������������� ������� (������ �� �������� 0)
//        sendbuf = new int[N * N];
//        printf("matrix:\n");
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                sendbuf[i * N + j] = rand() % 100;  // ���� ����� �� 0 �� 99
//                printf("%3d ", sendbuf[i * N + j]);
//            }
//            printf("\n");
//        }
//    }
//
//    // ����� ��� ��������� ����� �� ������ ��������
//    int* recvbuf = new int[rows_per_proc * N];
//
//    // �������� ����� ������� ����� ����������
//    MPI_Scatter(sendbuf, rows_per_proc * N, MPI_INT,
//        recvbuf, rows_per_proc * N, MPI_INT,
//        0, MPI_COMM_WORLD);
//
//    //const void* sendbuf,    // ��������� �� ������, �� �������� ������������ ������ (�� ��������-�����������).
//    //    int rows_per_proc,          // ���������� ���������, ������������ ������� ��������.
//    //    MPI_Datatype MPI_INT,  // ��� ������, ������������ ������� ��������.
//    //    void* recvbuf,          // ��������� �� �����, � ������� ����������� ������ (�� ������ ��������).
//    //    int recvcount,          // ���������� ���������, ����������� ������ ���������.
//    //    MPI_Datatype recvtype,  // ��� ������, ����������� ������ ���������.
//    //    int root,               // ���� ��������-����������� (������ 0).
//    //    MPI_Comm comm           // ������������, ��������, MPI_COMM_WORLD.
//
//    // ��������� ����� ��� �������� ������������ �������� �����
//    int* local_max = new int[rows_per_proc];
//
//    // ���������� ��������� � ������ ������, ������������� �� ������� ��������
//    for (int i = 0; i < rows_per_proc; i++) {
//        local_max[i] = recvbuf[i * N];  // �������������� �������� ������ ��������� ������
//        for (int j = 1; j < N; j++) {
//            local_max[i] = max(local_max[i], recvbuf[i * N + j]);
//        }
//    }
//
//    // ����� ��� ����� ���� ����������� (����� �������=0)
//    int* global_max = nullptr;
//    if (rank == 0) {
//        global_max = new int[N];
//    }
//
//    // ���� ��������� ���������� �� �������� 0
//    MPI_Gather(local_max, rows_per_proc, MPI_INT,
//        global_max, rows_per_proc, MPI_INT,
//        0, MPI_COMM_WORLD);
//
//    // ������ ����������� �� �������� 0
//    if (rank == 0) {
//        printf("\nMax in every row:\n");
//        for (int i = 0; i < N; i++) {
//            printf("row %d: %d\n", i, global_max[i]);
//        }
//    }
//
//    // ������������ ������
//    if (rank == 0) {
//        delete[] sendbuf;
//        delete[] global_max;
//    }
//    delete[] recvbuf;
//    delete[] local_max;
//
//    // ���������� MPI
//    MPI_Finalize();
//    return 0;
//}
