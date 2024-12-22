//#include <omp.h>
//#include <stdio.h>
//#include <time.h>
//
//#define N 10

//int main()
//{
//	int i;
//	double a[N + 1], b[N + 1], c[N + 1], d[N + 1];
//
//	/* Some initializations */
//	for (i = 0; i < N; i++) {
//		a[i] = i * 1.5;
//		b[i] = i + 22.35;
//	}
//
//	double start = omp_get_wtime();
//
//#pragma omp parallel num_threads(2) shared(a,b,c,d) private(i)
//	{
//#pragma omp sections nowait
//		{
//#pragma omp section
//			{
//				for (i = 0; i < N; i++)
//					c[i] = a[i] + b[i];
//				printf("I'm thread %d. Calculate vectors sum.\n", omp_get_thread_num());
//
//			}
//#pragma omp section
//			{
//				for (i = 0; i < N; i++)
//					d[i] = a[i] * b[i];
//				printf("I'm thread %d. Calculate vectors product.\n", omp_get_thread_num());
//
//			}
//		}  /* end of sections */
//	}  /* end of parallel section */
//
//	double end = omp_get_wtime();
//	printf("The time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//	return 0;
//}
// 0.0008





//#include <omp.h>
//#include <stdio.h>
//#include <time.h>
//
//#define N 10
//
//int main()
//{
//	int i;
//	double a[N + 1], b[N + 1], c[N + 1], d[N + 1];
//
//	/* Some initializations */
//	for (i = 0; i < N; i++) {
//		a[i] = i * 1.5;
//		b[i] = i + 22.35;
//	}
//
//	double start = omp_get_wtime();
//
//	for (i = 0; i < N; i++)
//		c[i] = a[i] + b[i];
//	printf("I'm thread %d. Calculate vectors sum.\n", omp_get_thread_num());
//
//	for (i = 0; i < N; i++)
//		d[i] = a[i] * b[i];
//	printf("I'm thread %d. Calculate vectors product.\n", omp_get_thread_num());
//	double end = omp_get_wtime();
//	printf("The time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//	return 0;
//}
 //0.0003



// SINGLE
//
//int main()
//{
//	int i;
//	double a[N + 1], b[N + 1], c[N + 1], d[N + 1];
//
//	/* Some initializations */
//	for (i = 0; i < N; i++) {
//		a[i] = i * 1.5;
//		b[i] = i + 22.35;
//	}
//
//	double start = omp_get_wtime();
//
//#pragma omp single
//	{
//		for (i = 0; i < N; i++)
//			c[i] = a[i] + b[i];
//		printf("I'm thread %d. Calculate vectors sum.\n", omp_get_thread_num());
//
//		{
//			for (i = 0; i < N; i++)
//				d[i] = a[i] * b[i];
//			printf("I'm thread %d. Calculate vectors product.\n", omp_get_thread_num());
//
//		}
//
//		double end = omp_get_wtime();
//		printf("The time to calculate xx was %lf seconds\n", ((double)(end - start) / 1.0));
//
//
//	}
//	return 0;
//}
// 0.0003