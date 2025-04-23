import numpy as np
import matplotlib.pyplot as plt

# Функция f(t, u), правая часть дифференциального уравнения
def f(t, u):
    return np.exp(3 * t) + 3 * (u - 1)

# Точное решение
def exact_solution(t):
    return np.exp(3 * t) + 3 * (np.exp(t) - 1)

# Метод Рунге-Кутта 3-го порядка
def runge_kutta3(t0, T, u0, tau):
    n = int((T - t0) / tau)
    t_values = np.linspace(t0, T, n + 1)
    u_values = np.zeros(n + 1)
    u_values[0] = u0

    for i in range(n):
        t_i = t_values[i]
        u_i = u_values[i]

        k1 = tau * f(t_i, u_i)
        k2 = tau * f(t_i + tau / 2, u_i + k1 / 2)
        k3 = tau * f(t_i + tau, u_i - k1 + 2 * k2)

        u_values[i + 1] = u_i + (1 / 6) * (k1 + 4 * k2 + k3)

    return t_values, u_values

# Метод Эйлера
def euler_method(f, t0, u0, T, tau):
    n = int((T - t0) / tau)
    t_values = np.linspace(t0, T, n + 1)
    u_values = np.zeros(n + 1)
    u_values[0] = u0

    for i in range(n):
        u_values[i + 1] = u_values[i] + tau * f(t_values[i], u_values[i])

    return t_values, u_values

# Метод предиктор-корректор
def predictor_corrector(t0, T, u0, tau):
    n = int((T - t0) / tau)
    t_values = np.linspace(t0, T, n + 1)
    u_values = np.zeros(n + 1)
    u_values[0] = u0

    for i in range(n):
        t_i = t_values[i]
        u_i = u_values[i]

        u_half = u_i + 0.5 * tau * f(t_i, u_i)
        t_half = t_i + 0.5 * tau

        u_values[i + 1] = u_i + tau * f(t_half, u_half)

    return t_values, u_values

# Метод Рунге-Кутта 4-го порядка
def runge_kutta4(t0, T, u0, tau):
    n = int((T - t0) / tau)
    t_values = np.linspace(t0, T, n + 1)
    u_values = np.zeros(n + 1)
    u_values[0] = u0

    for i in range(n):
        t_i = t_values[i]
        u_i = u_values[i]

        k1 = f(t_i, u_i)
        k2 = f(t_i + 0.5 * tau, u_i + 0.5 * tau * k1)
        k3 = f(t_i + 0.5 * tau, u_i + 0.5 * tau * k2)
        k4 = f(t_i + tau, u_i + tau * k3)

        u_values[i + 1] = u_i + (tau / 6) * (k1 + 2*k2 + 2*k3 + k4)

    return t_values, u_values

# Параметры задачи
t0 = 0
T = 1
u0 = 1
tau = 0.003125

# Вычисления для всех методов
t_values_euler, u_euler = euler_method(f, t0, u0, T, tau)
_, u_pred_corr = predictor_corrector(t0, T, u0, tau)
_, u_rk3 = runge_kutta3(t0, T, u0, tau)
_, u_rk4 = runge_kutta4(t0, T, u0, tau)
exact_values = exact_solution(t_values_euler)

# Форматированный вывод таблицы с выравниванием
print(f"{'i':<4}{'t':<8}{'Метод Эйлера':<20}{'Предиктор-корректор':<25}{'Метод Рунге-Кутта III':<25}{'Метод Рунге-Кутта IV':<25}{'Точное решение':<20}")
for i in range(len(t_values_euler)):
    print(f"{i:<4}{t_values_euler[i]:<8.1f}{u_euler[i]:<20.6f}{u_pred_corr[i]:<25.6f}{u_rk3[i]:<25.6f}{u_rk4[i]:<25.6f}{exact_values[i]:<20.6f}")
