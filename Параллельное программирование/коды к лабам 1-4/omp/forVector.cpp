#include <iostream>
#include <omp.h>
//#include <stdio.h>
//#include <time.h>
//
//#define CHUNKSIZE 100
//#define N 10000000
//char* a = new char[N];
//char* b = new char[N];
//char* c = new char[N];

///				PARALLEL ///////
 //time = 0.07
//int main()
//{
//	double start;
//	double end;
//	int i, chunk;
//
//	/* some initializations */
//	for (i = 0; i < N; i++)
//		a[i] = b[i] = (char)1;
//	chunk = CHUNKSIZE;
//	start = omp_get_wtime();
//#pragma omp parallel num_threads(4) shared(a,b,c,chunk) private(i)
//	{
//#pragma omp for schedule(dynamic,chunk) nowait
//		for (i = 0; i < N; i++) {
//			c[i] = a[i] + b[i];
//			//printf("i'm thread %d. calculate %d iteration\n", omp_get_thread_num(), i);
//		}
//	}  /* end of parallel section */
//	end = omp_get_wtime();
//	printf("the time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//	// освобождение динамически выделенной памяти
//	delete[] a;
//	delete[] b;
//	delete[] c;
//
//	std::cin >> end;
//	return 0;
//}

/////////////////////////////////////////// SINGLE /////////////////////////////////////////////
// time = 0.02
//int main()
//{
//	double start;
//	double end;
//	int i, chunk;
//
//	/* some initializations */
//	for (i = 0; i < N; i++)
//		a[i] = b[i] = (char)1;
//	chunk = CHUNKSIZE;
//	start = omp_get_wtime();
//#pragma omp single
//	{
//		for (i = 0; i < N; i++) {
//			c[i] = a[i] + b[i];
//			//printf("i'm thread %d. calculate %d iteration\n", omp_get_thread_num(), i);
//		}
//	}
//	end = omp_get_wtime();
//	printf("the time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//	// освобождение динамически выделенной памяти
//	delete[] a;
//	delete[] b;
//	delete[] c;
//
//	std::cin >> end;
//	return 0;
//}



//int main()
//{
//	double start;
//	double end;
//	int i, chunk;
//
//	/* Some initializations */
//	for (i = 0; i < N; i++)
//		a[i] = b[i] = (char)1;
//	chunk = CHUNKSIZE;
//	start = omp_get_wtime();
//	for (i = 0; i < N; i++) {
//		c[i] = a[i] + b[i];
//		//printf("I'm thread %d. Calculate %d iteration\n", omp_get_thread_num(), i);
//	}
//	end = omp_get_wtime();
//	printf("The time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//	// Освобождение динамически выделенной памяти
//	delete[] a;
//	delete[] b;
//	delete[] c;
//
//	std::cin >> end;
//	return 0;
//}