#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Структура для хранения коэффициентов сплайна на каждом интервале
struct Spline {
    double a, b, c, d, x;
};

// Функция для построения кубического сплайна
vector<Spline> buildCubicSpline(const vector<double>& x, const vector<double>& y, double S_a, double S_b) {
    int n = x.size();
    vector<double> h(n - 1), alpha(n - 1), l(n), mu(n), z(n);
    vector<Spline> splines(n - 1);

    // Вычисление шагов между узлами и значений alpha для системы уравнений
    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
        alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // Установка граничных условий
    l[0] = 2 * h[0];
    mu[0] = 0.5;
    z[0] = alpha[0] / l[0];
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = h[n - 2] * (2 - mu[n - 2]);
    z[n - 1] = (alpha[n - 2] - h[n - 2] * z[n - 2]) / l[n - 1];

    vector<double> c(n), b(n - 1), d(n - 1);

    c[n - 1] = z[n - 1];
    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    // Создание структуры сплайнов
    for (int i = 0; i < n - 1; ++i) {
        splines[i] = { y[i], b[i], c[i], d[i], x[i] };
    }

    return splines;
}

// Функция для вычисления значения сплайна в точке
double evaluateSpline(const vector<Spline>& splines, double x_val) {
    Spline s;
    for (const auto& spline : splines) {
        if (x_val >= spline.x) {
            s = spline;
        }
        else {
            break;
        }
    }
    double dx = x_val - s.x;
    return s.a + s.b * dx + s.c * dx * dx + s.d * dx * dx * dx;
}

int main() {
    // Исходные данные
    vector<double> x = { 1, 1.1, 1.17, 1.23, 1.3, 1.35, 1.41, 1.5, 1.56, 1.6, 1.64, 1.7, 1.75, 1.8, 1.89, 1.93, 2 };
    vector<double> y = { 4.041, 3.340, 2.978, 2.718, 2.449, 2.269, 2.056, 1.726, 1.493, 1.331, 1.162, 0.900, 0.676, 0.450, 0.057, -0.106, -0.357 };

    double S_a = -8.5194; // Граничное условие производной в начале
    double S_b = -3.21457; // Граничное условие производной в конце

    // Построение сплайна
    auto splines = buildCubicSpline(x, y, S_a, S_b);

    // Вычисление значения сплайна в точке x* = 1.95
    double x_star = 1.95;
    double spline_value = evaluateSpline(splines, x_star);

    cout << "Значение сплайна в точке x* = " << x_star << ": " << spline_value << endl;

    return 0;
}
