//#include <iostream>
//#include <cmath>
//#include <omp.h>
//#include <stdio.h>
//#include <vector>
//#include <ctime>
//#include <random>
//
//// 1
//// нужно было распараллелить алгоритм вычисления нормы вектора
//
// //using namespace std;
//
// //int main() {
// //  setlocale(LC_ALL, "ru");
//
// //  vector<int> x;
// //  int n, i, a;
// //  double sum = 0.0;
// //  cout << "Введите размерность вектора: ";
// //  cin >> n;
// //  for (i = 0; i < n; i++) {
// //    cout << "Введите число: ";
// //    cin >> a;
// //    x.push_back(a);
// //  }
// //  #pragma omp parallel
// //  {
// //    #pragma omp for reduction(+:sum)
// //    for (i = 0; i < n; i++)
// //    { 
// //      sum += pow(x[i], 2);
// //    }
// //  }
// //  printf("\nнорма вектора: %.2f\n", sqrt(sum));
// //}
//
//// 2
//
// // нужно было распараллелить алгоритм вычисления максимальной суммы из всех строк матрицы
//
//
//using namespace std;
//
//int main() {
//    setlocale(LC_ALL, "ru");
//    vector<vector<int>> A = {
//        {1, 2, 2},
//        {-3, 2, 1},
//        {1, -10, 1}
//    };
//    int n = A.size();
//    int summax = -1;
//
//#pragma omp parallel for reduction(max:summax) shared(A)
//    for (int i = 0; i < n; i++) {
//        int local_sum = 0;
//        for (int j = 0; j < A[i].size(); j++) {
//            local_sum += abs(A[i][j]);
//        }
//        if (local_sum > summax) {
//            summax = local_sum;
//        }
//    }
//
//    cout << "Максимальная сумма из всех строк матрицы: " << summax << endl;
//    return 0;
//}
//
//
//
//
//
//
//
//using namespace std;
//
//int main() {
//    vector<vector<int>> A = { 
//        {1, 2, 2},
//        {-3, 2, 1},
//        {1, -10, 1} 
//    };
//    int i, j, n = A.size(), summax = -1;
//
//#pragma omp parallel shared(A, summax) private(i, j)
//    {
//        int local_sum;  // Локальная переменная для накопления суммы
//#pragma omp for
//        for (i = 0; i < n; i++) {
//            local_sum = 0;
//            for (j = 0; j < A[i].size(); j++) {
//                local_sum += abs(A[i][j]);
//            }
//
//            // critical для безопасного обновления глобального максимума суммы
//#pragma omp critical
//            {
//                if (local_sum > summax) {
//                    summax = local_sum;
//                }
//            }
//        }
//    }
//
//    cout << "Max sum (abs): " << summax << endl;
//    return 0;
//}