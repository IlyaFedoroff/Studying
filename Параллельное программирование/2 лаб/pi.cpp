//#include <stdio.h>
//#include <time.h>
//#include <omp.h>
//
//long long num_steps = 1000000000;
//double step;
//
//int main(int argc, char* argv[])
//{
//	clock_t start, stop;
//	double x, pi, sum = 0.0;
//	int i;
//	step = 1. / (double)num_steps;
//	start = clock();
//
//#pragma omp parallel private(x) shared(sum)
//	{
//#pragma omp for
//		for (i = 0; i < num_steps; i++)
//		{
//			x = (i + .5) * step;
//			sum = sum + 4.0 / (1. + x * x);
//			//printf("Hello, world! %d", omp_get_thread_num());
//		}
//	}
//
//
//	pi = sum * step;
//	stop = clock();
//
//	printf("The value of PI is %15.12f\n", pi);
//	printf("The time to calculate PI was %f seconds\n", ((double)(stop - start) / 1000.0));
//	return 0;
//}