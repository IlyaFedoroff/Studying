//#include <omp.h>
//#include <stdio.h>
//
//int main(void)
//{
//	
//	
//	int max_threads = omp_get_max_threads();
//	printf("max threads: %d\n", max_threads);
//	omp_set_num_threads(8);
//
//#pragma omp parallel
//	{
//		int threads = omp_get_num_threads();
//		int tid = omp_get_thread_num();
//		printf("Hello, world! I am %d from %d threads!\n", tid, threads);
//	}
//	return 0;
//}
