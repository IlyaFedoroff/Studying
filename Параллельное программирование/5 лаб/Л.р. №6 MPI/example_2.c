/*
 * Пример 2 
 * Разбиение всего множества процессов на две группы с использованием функции MPI_Comm_split
 */

void main(int argc, char *argv[])
{
	int rank, size, color;
	MPI_Comm NEW_COMM;
	
   	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	color = rank%2;
	MPI_Comm_split(MPI_COMM_WORLD, color, 1, &NEW_COMM);
	MPI_Comm_rank(NEW_COMM,&rank);
	
	printf("My rank in NEW_COMM = %d, my color = %d\n", rank, color);

	MPI_Comm_free(&NEW_COMM);
	MPI_Finalize();
}

