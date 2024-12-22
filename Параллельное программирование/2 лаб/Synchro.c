//#include <omp.h>
//#include <stdio.h>
//
//int main ()
//{
//  int x;
//  x = 0;
//
//  #pragma omp parallel num_threads(3)
//  {
//	#pragma omp critical 
//        x = x + 1;
//	printf("[%d]: x = %d", omp_get_thread_num(), x);
//
//    #pragma omp barrier
//
//    #pragma omp master
//	  printf("I'am master!");
//  }
//  return 0;
//}