#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;


// Сохранение результатов в файл для построения графиков
void saveResultsToFile(const vector<double>& epsilons, const vector<int>& powerIterations,
    const vector<int>& scalarIterations, const vector<int>& rayleighIterations,
    const vector<int>& inverseIterations) {
    ofstream file("convergence_data.csv");
    file << "epsilon,PowerMethod,ScalarProductMethod,RayleighQuotientMethod,InverseIterationMethod\n";
    for (size_t i = 0; i < epsilons.size(); ++i) {
        file << epsilons[i] << "," << powerIterations[i] << ","
            << scalarIterations[i] << "," << rayleighIterations[i] << ","
            << inverseIterations[i] << "\n";
    }
    file.close();
}


// Евклидова норма вектора
double vectorNorm(const vector<double>& v) {
    double norm = 0.0;
    for (double x : v) {
        norm += x * x;
    }
    return sqrt(norm);
}

//нормировка векторов y(k) вводится в алгоритм, для того, чтобы
//при достаточно большом числе итераций предотвратить превышение
//допустимых для компьютера чисел при | λ1 | > 1 или пропадание
//значащих цифр при | λ1 | < 1 итерированных векторов за счет
//множителя λ1k
//
//нормализация вектора, делим элементы на норму
void normalize(vector<double>& v) {
    double norm = vectorNorm(v);
    for (double& x : v) {
        x /= norm;
    }
}

// умножение матрицы на вектор
vector<double> matrixVectorMultiply(const vector<vector<double>>& A, const vector<double>& v) {
    int n = A.size();
    vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * v[j];
        }
    }
    return result;
}

// Функция для вычисления скалярного произведения двух векторов
double dotProduct(const vector<double>& v1, const vector<double>& v2) {
    double result = 0.0;
    for (int i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}


// Реализация функции нахождения обратной матрицы
vector<vector<double>> inverse(const vector<vector<double>>& A) {

    int n = 5;

    vector<vector<double>> a_copy = A;  // Копия матрицы
    vector<vector<double>> inv(n, vector<double>(n, 0));    // расш матрица

    // Создаем расширенную матрицу [A|I]
    for (int i = 0; i < n; ++i) {
        inv[i][i] = 1.0;  // единичная матрица
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента для выбора главного элемента
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(a_copy[k][i]) > abs(a_copy[max_row][i])) {
                max_row = k;
            }
        }

        // Меняем строки местами в обоих матрицах (A и единичная часть)
        swap(a_copy[i], a_copy[max_row]);
        swap(inv[i], inv[max_row]);

        // Нормализуем строку, делая главный элемент равным 1
        double diag_elem = a_copy[i][i];
        for (int j = 0; j < n; ++j) {
            a_copy[i][j] /= diag_elem;
            inv[i][j] /= diag_elem;
        }

        // Обнуление элементов ниже и выше главного элемента
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = a_copy[k][i];
                for (int j = 0; j < n; ++j) {
                    a_copy[k][j] -= factor * a_copy[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    return inv;
}


// Степенной метод
pair<double, int> powerMethod(const vector<vector<double>>& A, double epsilon) {
    int n = A.size();
    vector<double> y(n, 1.0); // Задаем начальный ненулевой вектор y0
    normalize(y); // Нормируем начальный вектор

    vector<double> lambda_old(n, 0.0); // Вектор для хранения предыдущих значений лямбда
    vector<double> lambda_new(n, 0.0); // Вектор для текущих значений лямбда

    int iterations = 0;

    while (true) {
        // Шаг 3: Вычисляем y^k = A * y^(k-1)
        vector<double> y_new = matrixVectorMultiply(A, y);

        // Шаг 4: Вычисляем лямбда^k = y^k / y^(k-1)
        for (int i = 0; i < n; ++i) {
            lambda_new[i] = y_new[i] / (y[i] + std::numeric_limits<double>::epsilon()); // добавляем epsilon для избегания деления на 0
        }

        // Шаг 5: Проверяем условие сходимости
        double max_diff = 0.0;
        for (int i = 0; i < n; ++i) {
            max_diff = max(max_diff, fabs(lambda_new[i] - lambda_old[i]));
        }

        if (max_diff < epsilon) {
            // Если достигнута сходимость, возвращаем наибольшее по модулю собственное значение
            double max_lambda = *max_element(lambda_new.begin(), lambda_new.end(), [](double a, double b) { return fabs(a) < fabs(b); });
            return { max_lambda, iterations };
        }

        // Обновляем значения для следующей итерации
        lambda_old = lambda_new;
        y = y_new;
        normalize(y); // Нормируем вектор y^(k-1)
        iterations++;
    }
}

//pair<double, int> powerMethod(const vector<vector<double>>& A, double epsilon) {
//    int n = A.size();
//    vector<double> y(n, 1.0); // начальный ненулевой вектор
//    normalize(y); // нормируем начальный вектор
//
//    vector<double> lambda_old(n, 0.0); // Вектор предыдущих собственных значений
//    vector<double> lambda_new(n, 0.0); // Вектор новых собственных значений
//    int iterations = 0;
//
//    do {
//        vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)
//        normalize(y_new);
//
//        // Вычисление вектора новых собственных значений
//        for (int i = 0; i < n; ++i) {
//            lambda_new[i] = y_new[i] / y[i];
//        }
//
//        // Нахождение максимальной разности между новым и старым векторами собственных значений
//        double max_diff = 0.0;
//        for (int i = 0; i < n; ++i) {
//            max_diff = max(max_diff, fabs(lambda_new[i] - lambda_old[i]));
//        }
//        cout << "Лямбда в степенном: " << max_diff << endl;
//        iterations++;
//        if (max_diff < epsilon) break;
//
//        lambda_old = lambda_new; // Обновляем старый вектор собственных значений
//        y = y_new; // Обновляем вектор y
//
//    } while (true);
//
//    return { lambda_new[0], iterations };
//}




// Метод скалярных произведений для нахождения наибольшего собственного числа
pair<double, int> scalarProductsMethod(const vector<vector<double>>& A, double epsilon) {
    int n = A.size();
    vector<double> y(n, 1.0); // начальный ненулевой вектор
    normalize(y); // нормируем начальный вектор

    double lambda_old = 0.0, lambda_new = 0.0;
    int iterations = 0;

    do {
        vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)

        // Вычисляем скалярные произведения
        double dot_yk_yk = dotProduct(y_new, y_new);        // (y(k), y(k))
        double dot_yk_yk1 = dotProduct(y_new, y);           // (y(k), y(k-1))

        // Обновляем новое собственное значение как отношение скалярных произведений
        lambda_new = dot_yk_yk / dot_yk_yk1;
        //cout << "Лямбда в скалярах: " << lambda_new << endl;

        // Нормализуем вектор y(k) для предотвращения переполнения
        normalize(y_new);

        // Проверяем условие сходимости
        if (fabs(lambda_new - lambda_old) < epsilon) break;

        lambda_old = lambda_new; // Обновляем старое значение λ
        y = y_new; // Обновляем вектор y
        iterations++;

    } while (true);

    return { lambda_new, iterations };
}

// Метод частных Рэлея для нахождения наибольшего собственного значения
pair<double, int> rayleighMethod(const vector<vector<double>>& A, double epsilon) {
    int n = A.size();
    vector<double> y(n, 1.0); // начальный ненулевой вектор
    normalize(y); // нормируем начальный вектор

    double lambda_old = 0.0, lambda_new = 0.0;
    int iterations = 0;

    do {
        vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)

        // Вычисляем функционал Рэлея как скалярное произведение
        double dot_yk_yk1 = dotProduct(y_new, y);   // (y(k), y(k-1))
        double dot_yk1_yk1 = dotProduct(y, y);        // (y(k-1), y(k-1))

        // Обновляем новое собственное значение как отношение скалярных произведений
        lambda_new = dot_yk_yk1 / dot_yk1_yk1;

        // Нормируем новый вектор y(k) для предотвращения переполнения
        normalize(y_new);

        // Проверяем условие сходимости
        if (fabs(lambda_new - lambda_old) < epsilon) break;

        lambda_old = lambda_new; // Обновляем старое значение λ
        y = y_new; // Обновляем вектор y
        iterations++;

    } while (true);

    // Возвращаем найденное собственное значение и собственный вектор
    return { lambda_new, iterations };
}

// Решение системы линейных уравнений методом Гаусса
vector<double> solveLinearSystem(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<vector<double>> augmented(A);
    vector<double> x = b;

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double factor = augmented[j][i] / augmented[i][i];
            for (int k = i; k < n; ++k) {
                augmented[j][k] -= factor * augmented[i][k];
            }
            x[j] -= factor * x[i];
        }
    }

    // Обратный ход метода Гаусса
    vector<double> result(n);
    for (int i = n - 1; i >= 0; --i) {
        result[i] = x[i] / augmented[i][i];
        for (int j = i - 1; j >= 0; --j) {
            x[j] -= augmented[j][i] * result[i];
        }
    }

    return result;
}
// Метод обратных итераций для нахождения наименьшего собственного числа
pair<double, int> inverseIterationMethod(const vector<vector<double>>& A, double epsilon) {
    int n = A.size();
    vector<double> y(n, 1.0); // начальный ненулевой вектор
    normalize(y); // нормируем начальный вектор

    double lambda_old = 0.0, lambda_new = 0.0;
    int iterations = 0;
    double tempU = 0;

    do {
        // y(k) = [обратная матрицаA] * y(k-1)
        vector<double> y_new = matrixVectorMultiply(A, y);

        // Нормируем новый вектор y(k) для предотвращения переполнения
        normalize(y_new);

        // Вычисляем скалярные произведения
        double dot_yk_yk1 = dotProduct(y_new, y);        // (y(k), y(k-1))
        double dot_yk_yk = dotProduct(y_new, y_new);     // (y(k), y(k))

        // Обновляем новое собственное значение как отношение скалярных произведений
        tempU = dot_yk_yk1 / dot_yk_yk;
        lambda_new = 1 / tempU;

        // Проверяем условие сходимости
        if (fabs(lambda_new - lambda_old) < epsilon) break;

        lambda_old = lambda_new; // Обновляем старое значение λ
        y = y_new; // Обновляем вектор y
        iterations++;

    } while (true);

    return { lambda_new, iterations };
}


// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& A) {
    for (const auto& row : A) {
        for (const auto& elem : row) {
            cout << setw(10) << setprecision(4) << elem << " "; // Установка ширины и точности
        }
        cout << endl; // Переход на новую строку после каждой строки матрицы
    }
}


//vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)

int main() {
    setlocale(LC_ALL, "rus");
    vector<vector<double>> A = {
        {11, 2.2, 3.1, 4, 5},
        {2.2, 23, 0, 0.14, 0},
        {3.1, 0, 11, 0.2, 5.1},
        {4, 0.14, 0.2, 13, 2.9},
        {5, 0, 5.1, 2.9, 10}
    };

    vector<vector<double>> AInv = inverse(A);
    //printMatrix(AInv);

    vector<double> epsilons = { 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9 };
    vector<int> powerIterations, scalarIterations, rayleighIterations, inverseIterations;

    cout << fixed << setprecision(8);
    cout << setw(15) << "Метод" << setw(15) << "epsilon" << setw(20) << "Собственное значение" << setw(15) << "Итерации" << endl;
    cout << "=========================================================================================" << endl;

    for (double epsilon : epsilons) {
        auto resultPower = powerMethod(A, epsilon);
        powerIterations.push_back(resultPower.second);
        cout << setw(15) << "Степенной" << setw(15) << epsilon << setw(20) << resultPower.first << setw(15) << resultPower.second << endl;

        auto resultScalar = scalarProductsMethod(A, epsilon);
        scalarIterations.push_back(resultScalar.second);
        cout << setw(15) << "Скалярных" << setw(15) << epsilon << setw(20) << resultScalar.first << setw(15) << resultScalar.second << endl;

        auto resultRayleigh = rayleighMethod(A, epsilon);
        rayleighIterations.push_back(resultRayleigh.second);
        cout << setw(15) << "Рэлея" << setw(15) << epsilon << setw(20) << resultRayleigh.first << setw(15) << resultRayleigh.second << endl;

        auto resultInverse = inverseIterationMethod(AInv, epsilon);
        //auto resultInverse = powerMethod(AInv, epsilon);
        inverseIterations.push_back(resultInverse.second);
        cout << setw(15) << "Обратных" << setw(15) << epsilon << setw(20) << resultInverse.first << setw(15) << resultInverse.second << endl;

        cout << "-----------------------------------------------------------------------------------------" << endl;
    }

    saveResultsToFile(epsilons, powerIterations, scalarIterations, rayleighIterations, inverseIterations);

    return 0;


}


























//
//
//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <iomanip>
//
//using namespace std;
//
//
//// Евклидова норма вектора
//double vectorNorm(const vector<double>& v) {
//    double norm = 0.0;
//    for (double x : v) {
//        norm += x * x;
//    }
//    return sqrt(norm);
//}
//
////нормировка векторов y(k) вводится в алгоритм, для того, чтобы
////при достаточно большом числе итераций предотвратить превышение
////допустимых для компьютера чисел при | λ1 | > 1 или пропадание
////значащих цифр при | λ1 | < 1 итерированных векторов за счет
////множителя λ1k
////
////нормализация вектора, делим элементы на норму
//void normalize(vector<double>& v) {
//    double norm = vectorNorm(v);
//    for (double& x : v) {
//        x /= norm;
//    }
//}
//
//// умножение матрицы на вектор
//vector<double> matrixVectorMultiply(const vector<vector<double>>& A, const vector<double>& v) {
//    int n = A.size();
//    vector<double> result(n, 0.0);
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            result[i] += A[i][j] * v[j];
//        }
//    }
//    return result;
//}
//
//// Функция для вычисления скалярного произведения двух векторов
//double dotProduct(const vector<double>& v1, const vector<double>& v2) {
//    double result = 0.0;
//    for (int i = 0; i < v1.size(); ++i) {
//        result += v1[i] * v2[i];
//    }
//    return result;
//}
//
//
//pair<double, vector<double>> powerMethod(const vector<vector<double>>& A, double epsilon, int& iterations) {
//    int n = A.size();
//    vector<double> y(n, 1.0); // начальный ненулевой вектор
//    normalize(y); // нормируем начальный вектор
//
//    vector<double> lambda_old(n, 0.0); // Вектор предыдущих собственных значений
//    vector<double> lambda_new(n, 0.0); // Вектор новых собственных значений
//    iterations = 0;
//
//    do {
//        vector<double> y_new = matrixVectorMultiply(A, y);
//        normalize(y_new);
//
//        // Вычисление вектора новых собственных значений
//        for (int i = 0; i < n; ++i) {
//            lambda_new[i] = y_new[i] / y[i];
//        }
//
//        // Нахождение максимальной разности между новым и старым векторами собственных значений
//        double max_diff = 0.0;
//        for (int i = 0; i < n; ++i) {
//            max_diff = max(max_diff, fabs(lambda_new[i] - lambda_old[i]));
//        }
//
//        iterations++;
//        if (max_diff < epsilon) break;
//
//        lambda_old = lambda_new; // Обновляем старый вектор собственных значений
//        y = y_new; // Обновляем вектор y
//
//    } while (true);
//
//    return { lambda_new[0], y };
//}
//
//
//
//
//// Метод скалярных произведений для нахождения наибольшего собственного числа
//pair<double, vector<double>> scalarProductMethod(const vector<vector<double>>& A, double epsilon, int& iterations) {
//    int n = A.size();
//    vector<double> y(n, 1.0); // начальный ненулевой вектор
//    normalize(y); // нормируем начальный вектор
//
//    double lambda_old = 0.0, lambda_new = 0.0;
//    iterations = 0;
//
//    do {
//        vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)
//
//        // Вычисляем скалярные произведения
//        double dot_yk_yk = dotProduct(y_new, y_new);        // (y(k), y(k))
//        double dot_yk_yk1 = dotProduct(y_new, y);           // (y(k), y(k-1))
//
//        // Обновляем новое собственное значение как отношение скалярных произведений
//        lambda_new = dot_yk_yk / dot_yk_yk1;
//
//        // Нормализуем вектор y(k) для предотвращения переполнения
//        normalize(y_new);
//
//        // Проверяем условие сходимости
//        if (fabs(lambda_new - lambda_old) < epsilon) break;
//
//        lambda_old = lambda_new; // Обновляем старое значение λ
//        y = y_new; // Обновляем вектор y
//        iterations++;
//
//    } while (true);
//
//    // Возвращаем найденное собственное значение и собственный вектор
//    return { lambda_new, y };
//}
//
//// Метод частных Рэлея для нахождения наибольшего собственного значения
//pair<double, vector<double>> rayleighMethod(const vector<vector<double>>& A, double epsilon, int& iterations) {
//    int n = A.size();
//    vector<double> y(n, 1.0); // начальный ненулевой вектор
//    normalize(y); // нормируем начальный вектор
//
//    double lambda_old = 0.0, lambda_new = 0.0;
//    iterations = 0;
//
//    do {
//        vector<double> y_new = matrixVectorMultiply(A, y); // y(k) = A * y(k-1)
//
//        // Вычисляем функционал Рэлея как скалярное произведение
//        lambda_new = dotProduct(y_new, y) / dotProduct(y, y);
//
//        // Нормируем новый вектор y(k) для предотвращения переполнения
//        normalize(y_new);
//
//        // Проверяем условие сходимости
//        if (fabs(lambda_new - lambda_old) < epsilon) break;
//
//        lambda_old = lambda_new; // Обновляем старое значение λ
//        y = y_new; // Обновляем вектор y
//        iterations++;
//
//    } while (true);
//
//    // Возвращаем найденное собственное значение и собственный вектор
//    return { lambda_new, y };
//}
//
//// Решение системы линейных уравнений методом Гаусса
//vector<double> solveLinearSystem(const vector<vector<double>>& A, const vector<double>& b) {
//    int n = A.size();
//    vector<vector<double>> augmented(A);
//    vector<double> x = b;
//
//    // Прямой ход метода Гаусса
//    for (int i = 0; i < n; ++i) {
//        for (int j = i + 1; j < n; ++j) {
//            double factor = augmented[j][i] / augmented[i][i];
//            for (int k = i; k < n; ++k) {
//                augmented[j][k] -= factor * augmented[i][k];
//            }
//            x[j] -= factor * x[i];
//        }
//    }
//
//    // Обратный ход метода Гаусса
//    vector<double> result(n);
//    for (int i = n - 1; i >= 0; --i) {
//        result[i] = x[i] / augmented[i][i];
//        for (int j = i - 1; j >= 0; --j) {
//            x[j] -= augmented[j][i] * result[i];
//        }
//    }
//
//    return result;
//}
//
//// Метод обратных итераций для нахождения наименьшего собственного числа
//pair<double, vector<double>> inverseIterationMethod(const vector<vector<double>>& A, double epsilon, int& iterations) {
//    int n = A.size();
//    vector<double> y(n, 1.0); // начальный ненулевой вектор
//    normalize(y); // нормируем начальный вектор
//
//    double lambda_old = 0.0, lambda_new = 0.0;
//    iterations = 0;
//
//    do {
//        // Решаем систему A * y_new = y
//        vector<double> y_new = solveLinearSystem(A, y);
//
//        // Нормируем новый вектор y(k) для предотвращения переполнения
//        normalize(y_new);
//
//        // Вычисляем собственное значение как отношение скалярных произведений
//        lambda_new = dotProduct(y_new, y) / dotProduct(y, y);
//
//        // Проверяем условие сходимости
//        if (fabs(lambda_new - lambda_old) < epsilon) break;
//
//        lambda_old = lambda_new; // Обновляем старое значение λ
//        y = y_new; // Обновляем вектор y
//        iterations++;
//
//    } while (true);
//
//    // Возвращаем наименьшее собственное значение и соответствующий собственный вектор
//    return { lambda_new, y };
//}
//
//int main() {
//    setlocale(LC_ALL, "rus");
//    vector<vector<double>> A = {
//        {11, 2.2, 3.1, 4, 5},
//        {2.2, 23, 0, 0.14, 0},
//        {3.1, 0, 11, 0.2, 5.1},
//        {4, 0.14, 0.2, 13, 2.9},
//        {5, 0, 5.1, 2.9, 10}
//    };
//
//
//    double epsilon = 1e-5;
//    int iterations = 0;
//
//    auto result = inverseIterationMethod(A, epsilon, iterations);
//    cout << "Наименьшее собственное значение: " << result.first << endl;
//    cout << "Собственный вектор: ";
//    for (double val : result.second) {
//        cout << val << " ";
//    }
//    cout << endl;
//    cout << "Количество итераций: " << iterations << endl;
//
//    /*double epsilon = 1e-5;
//    int iterations = 0;
//
//    auto result = rayleighMethod(A, epsilon, iterations);
//    cout << "Наибольшее собственное значение: " << result.first << endl;
//    cout << "Собственный вектор: ";
//    for (double val : result.second) {
//        cout << val << " ";
//    }
//    cout << endl;
//    cout << "Количество итераций: " << iterations << endl;*/
//
//    /*double epsilon = 1e-6;
//    int iterationsPowerMethod = 0;
//    int iterationsScalarProductMethod = 0;
//
//    pair<double, vector<double>> answerPowerMethod = powerMethod(A, epsilon, iterationsPowerMethod);
//
//    pair<double, vector<double>> answerScalarProductMethod = scalarProductMethod(A, epsilon, iterationsScalarProductMethod);
//
//
//    double lambdaPower = answerPowerMethod.first;
//    vector<double> vectorPower = answerPowerMethod.second;
//
//
//    double lambdaScalar = answerScalarProductMethod.first;
//    vector<double> vectorScalar = answerScalarProductMethod.second;
//
//    cout << "Наибольшее собственное число: " << lambdaPower << endl;
//    cout << "Собственный вектор: ";
//    for (double x : vectorPower) {
//        cout << x << " ";
//    }
//    cout << endl;
//    cout << "Количество итераций: " << iterationsPowerMethod << endl;
//
//    cout << "Наибольшее собственное число: " << lambdaScalar << endl;
//    cout << "Собственный вектор: ";
//    for (double x : vectorScalar) {
//        cout << x << " ";
//    }
//    cout << endl;
//    cout << "Количество итераций: " << iterationsScalarProductMethod << endl;*/
//
//    return 0;
//}
