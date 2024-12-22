#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);               // ������������� MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ��������� ����� �������� ��������
    MPI_Comm_size(MPI_COMM_WORLD, &size); // ��������� ������ ����� ���������

    std::cout << "Hello from process " << rank << " of " << size << std::endl;

    MPI_Finalize(); // ���������� ������ MPI
    return 0;
}
