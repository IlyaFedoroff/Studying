//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <omp.h>
//
//int main()
//{
//    int n = 100000, i; double pi, h, sum, x;
//    omp_lock_t lck;
//    h = 1.0 / (double)n;
//    sum = 0.0;
//    omp_init_lock(&lck);
//#pragma omp parallel default (none) private (i,x) shared (n,h,sum,lck)
//    {
//        double local_sum = 0.0;
//#pragma omp for nowait
//        for (i = 1; i <= n; i++) {
//            x = h * ((double)i - 0.5);
//            local_sum += (4.0 / (1.0 + x * x));
//        }
//        omp_set_lock(&lck);
//        sum += local_sum;
//        omp_unset_lock(&lck);
//    }
//    pi = h * sum;
//    printf("pi is approximately %.16f", pi);
//    omp_destroy_lock(&lck);
//    return 0;
//}


//#include <stdio.h>
//
//
//int main()
//{
//	int n = 100000, i; double pi, h, sum, x;
//	h = 1.0 / (double)n;
//	sum = 0.0;
//
//	for (i = 1; i <= n; i++) {
//		x = h * ((double)i - 0.5);
//		sum += (4.0 / (1.0 + x * x));
//	}
//
//	pi = h * sum;
//	printf("pi is approximately %.16f", pi);
//
//	return 0;
//}