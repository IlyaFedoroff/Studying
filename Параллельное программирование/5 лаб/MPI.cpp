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
//	int N = 8;
//
//	if (argc == 2) {
//		N = atoi(argv[1]);
//	}
//
//	srand(time(NULL));
//	int size, rank, sendcount, recvcount, source;
//	int* sendbuf;
//	int counter = 0;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//
//
//	//Функция MPI_Comm_rank получает номер процесса(rank) в текущем коммуникаторе.Номер процесса — это уникальный идентификатор процесса
//	//    в рамках коммуникатора.
//	//    MPI_COMM_WORLD — это специальный коммуникатор, который включает все процессы,
//	//    запущенные с использованием MPI.Все процессы, выполняющиеся в программе, принадлежат этому коммуникатору,
//	//    если не указано иначе.
//	//    & rank — указатель на переменную, в которую будет записан номер процесса.
//
//	if (N % size) {
//		if (rank == 0) printf("Not good value of strings\n");
//		MPI_Finalize();
//		return 0;
//	}
//
//
//	sendbuf = new int[N * N];
//
//	if (rank == 0) printf("\n");
//	for (int i = 0; i < N; i++) {
//
//		for (int j = 0; j < N; j++) {
//			sendbuf[i * N + j] = rand() % 10;
//			if (rank == 0) printf("%d ", sendbuf[i * N + j]);
//			//printf("[%d],rank: %d ", sendbuf[i * N + j], rank);
//		}
//		if (rank == 0) printf("\n");
//	}
//
//
//	MPI_Barrier(MPI_COMM_WORLD);    // синхронизация процессов
//
//
//	int* recvbuf = new int[N / size * N];   // буфер для получения данных
//
//	source = 0;
//
//	// рассылка строк матрицы между процессами
//	MPI_Scatter(sendbuf, N / size * N, MPI_INT, recvbuf, N / size * N, MPI_INT, source, MPI_COMM_WORLD);
//	//int MPI_Scatter(
//	//    const void* sendbuf,  // Указатель на массив данных (только у root)
//	//    int sendcount,        // Количество элементов для каждого процесса
//	//    MPI_Datatype sendtype,// Тип элементов в sendbuf
//	//    void* recvbuf,        // Локальный буфер для получения данных
//	//    int recvcount,        // Количество элементов, которые получит каждый процесс
//	//    MPI_Datatype recvtype,// Тип элементов в recvbuf
//	//    int root,             // Номер процесса-отправителя
//	//    MPI_Comm comm         // Коммуникатор
//	//);
//
//
//	int* row_max = new int[N / size];
//	//printf("\n Elememts of rank %d\n", rank);
//	for (int i = 0; i < N / size; i++)
//	{
//		//printf("\nnow at process: %d", rank);
//		row_max[i] = recvbuf[i * N]; // максимальное значение для локальных строк
//
//		for (int j = 1; j < N; j++)
//		{
//			if (recvbuf[i * N + j] > row_max[i]) {
//				row_max[i] = recvbuf[i * N + j];    //   обновление максимума строки
//			}
//		}
//	}
//
//	// Печать локальных данных и максимумов для каждой строки
//	printf("\nElements of rank %d:\n", rank);
//	for (int i = 0; i < N / size; i++) {
//		for (int j = 0; j < N; j++) {
//			printf(" %d", recvbuf[i * N + j]);
//		}
//		printf(" | Max: %d", row_max[i]);  // Печать максимума строки
//		printf("\n");
//	}
//
//
//	int* global_max = nullptr;
//	if (rank == 0) {
//		global_max = new int[N]; // Выделяем память под все строки
//	}
//
//	// Сбор данных от всех процессов на rank 0
//	MPI_Gather(row_max, N / size, MPI_INT, global_max, N / size, MPI_INT, 0, MPI_COMM_WORLD);
//
//	//int MPI_Gather(
//	//	const void* sendbuf,   // Буфер с локальными данными (например, row_max)
//	//	int sendcount,         // Количество элементов, отправляемых каждым процессом
//	//	MPI_Datatype sendtype, // Тип данных отправляемых элементов
//	//	void* recvbuf,         // Буфер на root для сбора данных
//	//	int recvcount,         // Количество элементов, которые root ожидает от каждого процесса
//	//	MPI_Datatype recvtype, // Тип данных принимаемых элементов
//	//	int root,              // Номер процесса-агрегатора
//	//	MPI_Comm comm          // Коммуникатор
//	//);
//
//
//	// Если процесс rank 0, выводим общий результат
//	if (rank == 0) {
//		printf("\nGlobal max values for all rows:\n");
//		for (int i = 0; i < N; i++) {
//			printf("Row %d: %d\n", i, global_max[i]);
//		}
//		delete[] global_max; // Освобождаем память
//	}
//
//
//
//	MPI_Finalize();
//
//	delete[] sendbuf;
//	delete[] recvbuf;
//	delete[] row_max;
//}
//
//
//
//
//
