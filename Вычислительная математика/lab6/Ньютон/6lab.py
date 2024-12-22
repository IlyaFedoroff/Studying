import numpy as np
import matplotlib.pyplot as plt
import pandas as pd;

# 17 Вариант
x_values = np.array([1, 1.1, 1.17, 1.23, 1.3, 1.35, 1.41, 1.5, 1.56, 1.6, 1.64, 1.7, 1.75, 1.8, 1.89, 1.93, 2.0])
y_values = np.array([4.041, 3.34, 2.978, 2.718, 2.449, 2.269, 2.056, 1.726, 1.493, 1.331, 1.162, 0.9,
                     0.676, 0.45, 0.057, -0.106, -0.357])
x_star = 1.95

# Вычисления разделенных разностей вперед
def find_razn(x, y):
    n = len(y)
    razn = np.zeros((n, n))
    razn[:, 0] = y
    for j in range(1, n):
        for i in range(n - j):
            razn[i, j] = (razn[i + 1, j - 1] - razn[i, j - 1]) / (x[i + j] - x[i])
    return razn[0]

# Функция построения и вычисления значения многочлена
def newton(x, y, x_star):
    coeffs = find_razn(x, y)
    n = len(coeffs)
    result = coeffs[0]
    product_term = 1.0
    for i in range(1, n):
        product_term *= (x_star - x[i - 1])
        result += coeffs[i] * product_term
    return result

# Исследование сходимости
def convergence(x_values, y_values, x_star):
    interpolated_values = []
    convergence_diff = []

    for i in range(2, len(x_values) + 1):  # Построение сеток с 2 до N точек
        x_subset = x_values[:i]
        y_subset = y_values[:i]
        value = newton(x_subset, y_subset, x_star)  # Интерполяция на текущей сетке
        interpolated_values.append(value)
        if i > 2:  # Вычисление разности с предыдущей сеткой
            convergence_diff.append(abs(value - interpolated_values[-2]))
        else:
            convergence_diff.append(None)  # Для первой сетки нет разности

    return interpolated_values, convergence_diff

# Проведение исследования
interpolated_values, convergence_diff = convergence(x_values, y_values, x_star)

# Подготовка данных для таблицы
num_points = list(range(2, len(interpolated_values) + 2))
data = {
    "Количество точек": num_points,
    "P(x*)": interpolated_values,
    "Разность с предыдущей сеткой": convergence_diff
}
df = pd.DataFrame(data)

# Вывод таблицы
print("Таблица исследования сходимости:")
print(df)

# Построение многочлена и вычисление значения
interpolated_value = newton(x_values, y_values, x_star)
print(f"Значение интерполяционного многочлена в точке x* = {x_star}: {interpolated_value}")

# Визуализация исследования
plt.figure(figsize=(10, 6))
plt.plot(range(2, len(interpolated_values) + 2), interpolated_values, 'o-', label='P(x*) для разных сеток')
plt.title('Сходимость интерполяции многочленом Ньютона')
plt.xlabel('Число точек в сетке')
plt.ylabel('P(x*)')
plt.grid(True)
plt.legend()
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(range(3, len(convergence_diff) + 3), convergence_diff, 'o-', label='Разности между соседними сетками')
plt.title('Сходимость разностей интерполяции')
plt.xlabel('Число точек в сетке')
plt.ylabel('Разность значений P(x*)')
plt.grid(True)
plt.legend()
plt.show()
