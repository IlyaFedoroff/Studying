#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);               // Инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получение ранга текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получение общего числа процессов

    std::cout << "Hello from process " << rank << " of " << size << std::endl;

    MPI_Finalize(); // Завершение работы MPI
    return 0;
}
