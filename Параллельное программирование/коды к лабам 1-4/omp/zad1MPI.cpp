//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <algorithm>  // Для std::max
//#include <locale.h>
//using namespace std;
//
//int main(int argc, char** argv) {
//    setlocale(LC_ALL, "RU"); // RU локализация консоли
//    int N = 8;  // Размер матрицы (по умолчанию 8x8)
//
//    if (argc == 2) {
//        N = atoi(argv[1]);  // Если передан аргумент, используем его как размер матрицы
//    }
//
//    srand(time(NULL));
//    int size, rank, sendcount, recvcount;
//    int* sendbuf = nullptr;
//
//    // Инициализация MPI
//    MPI_Init(&argc, &argv); // каждый процесс 
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // получает уникальный rank(номер) 
//    MPI_Comm_size(MPI_COMM_WORLD, &size);   // и общее количество процессов size
//
//    // Проверяем делимость количества строк на число процессов
//    if (N % size != 0) {
//        if (rank == 0) printf("The number of lines must be a multiple of the number of processes.\n");
//        MPI_Finalize();
//        return 0;
//    }
//
//    int rows_per_proc = N / size;  // Число строк, обрабатываемых каждым процессом
//
//    // главный процесс
//    if (rank == 0) {
//        // Инициализация матрицы (только на процессе 0)
//        sendbuf = new int[N * N];
//        printf("matrix:\n");
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                sendbuf[i * N + j] = rand() % 100;  // случ числа от 0 до 99
//                printf("%3d ", sendbuf[i * N + j]);
//            }
//            printf("\n");
//        }
//    }
//
//    // Буфер для получения строк на каждом процессе
//    int* recvbuf = new int[rows_per_proc * N];
//
//    // Рассылка строк матрицы между процессами
//    MPI_Scatter(sendbuf, rows_per_proc * N, MPI_INT,
//        recvbuf, rows_per_proc * N, MPI_INT,
//        0, MPI_COMM_WORLD);
//
//    //const void* sendbuf,    // Указатель на массив, из которого отправляются данные (на процессе-отправителе).
//    //    int rows_per_proc,          // Количество элементов, отправляемых каждому процессу.
//    //    MPI_Datatype MPI_INT,  // Тип данных, отправляемых каждому процессу.
//    //    void* recvbuf,          // Указатель на буфер, в который принимаются данные (на каждом процессе).
//    //    int recvcount,          // Количество элементов, принимаемых каждым процессом.
//    //    MPI_Datatype recvtype,  // Тип данных, принимаемых каждым процессом.
//    //    int root,               // Ранг процесса-отправителя (обычно 0).
//    //    MPI_Comm comm           // Коммуникатор, например, MPI_COMM_WORLD.
//
//    // Локальный буфер для хранения максимальных значений строк
//    int* local_max = new int[rows_per_proc];
//
//    // Вычисление максимума в каждой строке, распределённой на текущем процессе
//    for (int i = 0; i < rows_per_proc; i++) {
//        local_max[i] = recvbuf[i * N];  // Инициализируем максимум первым элементом строки
//        for (int j = 1; j < N; j++) {
//            local_max[i] = max(local_max[i], recvbuf[i * N + j]);
//        }
//    }
//
//    // Буфер для сбора всех результатов (когда процесс=0)
//    int* global_max = nullptr;
//    if (rank == 0) {
//        global_max = new int[N];
//    }
//
//    // Сбор частичных максимумов на процессе 0
//    MPI_Gather(local_max, rows_per_proc, MPI_INT,
//        global_max, rows_per_proc, MPI_INT,
//        0, MPI_COMM_WORLD);
//
//    // Печать результатов на процессе 0
//    if (rank == 0) {
//        printf("\nMax in every row:\n");
//        for (int i = 0; i < N; i++) {
//            printf("row %d: %d\n", i, global_max[i]);
//        }
//    }
//
//    // Освобождение памяти
//    if (rank == 0) {
//        delete[] sendbuf;
//        delete[] global_max;
//    }
//    delete[] recvbuf;
//    delete[] local_max;
//
//    // Завершение MPI
//    MPI_Finalize();
//    return 0;
//}
