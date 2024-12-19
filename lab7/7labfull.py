import math
import matplotlib.pyplot as plt

# Данные
x = [3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4]
y = [17.086, 19.098, 21.333, 23.813, 26.564, 29.615, 32.998, 36.747, 40.901, 45.502, 50.598]

# Метод Гаусса
def gauss_method(A, B):
    n = len(B)
    for i in range(n):
        # Выбор главного элемента
        max_row = i + max(range(n - i), key=lambda k: abs(A[i + k][i]))
        if i != max_row:
            A[i], A[max_row] = A[max_row], A[i]
            B[i], B[max_row] = B[max_row], B[i]

        # Нормализация текущей строки
        pivot = A[i][i]
        for j in range(i, n):
            A[i][j] /= pivot
        B[i] /= pivot

        for k in range(i + 1, n):
            factor = A[k][i]
            for j in range(i, n):
                A[k][j] -= factor * A[i][j]
            B[k] -= factor * B[i]

    # Обратный ход
    X = [0] * n
    for i in range(n - 1, -1, -1):
        X[i] = B[i] - sum(A[i][j] * X[j] for j in range(i + 1, n))
    return X

# Линейное приближение y = kx + b
def linear_approximation(x, y):
    n = len(x)
    sum_x = sum(x)
    sum_x2 = sum(xi**2 for xi in x)
    sum_y = sum(y)
    sum_xy = sum(x[i] * y[i] for i in range(n))

    k = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x**2)
    b = (sum_y - k * sum_x) / n
    return k, b

# Степенное приближение y = c * x^m
def power_approximation(x, y):
    z = [math.log(xi) for xi in x]
    g = [math.log(yi) for yi in y]
    n = len(x)

    sum_z = sum(z)
    sum_z2 = sum(zi**2 for zi in z)
    sum_g = sum(g)
    sum_zg = sum(z[i] * g[i] for i in range(n))

    A = [[sum_z2, sum_z], [sum_z, n]]
    B = [sum_zg, sum_g]
    m, ln_c = gauss_method(A, B)
    c = math.exp(ln_c)
    return c, m

# Экспоненциальное приближение y = a * e^(b*x)
def exponential_approximation(x, y):
    ln_y = [math.log(yi) for yi in y]
    n = len(x)

    sum_x = sum(x)
    sum_x2 = sum(xi**2 for xi in x)
    sum_ln_y = sum(ln_y)
    sum_x_ln_y = sum(x[i] * ln_y[i] for i in range(n))

    A = [[sum_x2, sum_x], [sum_x, n]]
    B = [sum_x_ln_y, sum_ln_y]
    b, ln_a = gauss_method(A, B)
    a = math.exp(ln_a)
    return a, b

# Функция для вычисления квадратичного отклонения
def calculate_sse(x, y, model_func):
    return sum((y[i] - model_func(x[i]))**2 for i in range(len(x)))

# Вычисление
k, b = linear_approximation(x, y)
c, m = power_approximation(x, y)
a, b_exp = exponential_approximation(x, y)

# Определение моделей
linear_model = lambda xi: k * xi + b
power_model = lambda xi: c * xi**m
exponential_model = lambda xi: a * math.exp(b_exp * xi)

# Вычисление SSE
sse_linear = calculate_sse(x, y, linear_model)
sse_power = calculate_sse(x, y, power_model)
sse_exponential = calculate_sse(x, y, exponential_model)

# Результаты
print("Линейное приближение:")
print(f"y = {k:.4f}x + {b:.4f}")
print(f"Квадратичное отклонение (SSE): {sse_linear:.4f}")

print("\nСтепенное приближение:")
print(f"y = {c:.4f} * x^{m:.4f}")
print(f"Квадратичное отклонение (SSE): {sse_power:.4f}")

print("\nЭкспоненциальное приближение:")
print(f"y = {a:.4f} * e^({b_exp:.4f}x)")
print(f"Квадратичное отклонение (SSE): {sse_exponential:.4f}")

# Построение графика
plt.scatter(x, y, color='blue', label='Данные')

# Линейная модель
plt.plot(x, [linear_model(xi) for xi in x], color='red', label=f'Линейное: y = {k:.4f}x + {b:.4f}')

# Степенная модель
plt.plot(x, [power_model(xi) for xi in x], color='green', label=f'Степенное: y = {c:.4f} * x^{m:.4f}')

# Экспоненциальная модель
plt.plot(x, [exponential_model(xi) for xi in x], color='orange', label=f'Экспоненциальное: y = {a:.4f} * e^({b_exp:.4f}x)')

# Настройка графика
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Аппроксимация: Линейное, Степенное и Экспоненциальное")
plt.grid()
plt.show()
