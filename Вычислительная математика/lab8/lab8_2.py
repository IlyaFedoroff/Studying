import math
import matplotlib.pyplot as plt

# Функция
def f(x):
    return x * math.exp(x)

# Метод левых прямоугольников
def left_rectangles(a, b, n):
    h = (b - a) / n
    result = 0
    for i in range(n):
        result += f(a + i * h)
    return result * h

# Метод правых прямоугольников
def right_rectangles(a, b, n):
    h = (b - a) / n
    result = 0
    for i in range(1, n + 1):
        result += f(a + i * h)
    return result * h

# Метод средних прямоугольников
def middle_rectangles(a, b, n):
    h = (b - a) / n
    result = 0
    for i in range(n):
        result += f(a + (i + 0.5) * h)
    return result * h

# Метод трапеций
def trapezoidal(a, b, n):
    h = (b - a) / n
    result = f(a) + f(b)
    for i in range(1, n):
        result += 2 * f(a + i * h)
    return result * h / 2

# Метод Симпсона
def simpsons(a, b, n):
    h = (b - a) / n
    result = f(a) + f(b)
    for i in range(1, n, 2):
        result += 4 * f(a + i * h)
    for i in range(2, n - 1, 2):
        result += 2 * f(a + i * h)
    return result * h / 3

# Проверка погрешности
def estimate_error(prev, current):
    return abs(current - prev)

# Функция для подсчета итераций до достижения заданной точности
def calculate_iterations(method, a, b, tolerance):
    n = 1
    prev_result = 0
    error = float('inf')
    count = 0

    while error > tolerance:
        n *= 2
        count += 1
        current_result = method(a, b, n)
        if count > 1:
            error = estimate_error(prev_result, current_result)
        prev_result = current_result

    return count, current_result

# Главная часть программы
a = 2
b = 3
tolerance = 1e-6

# Список методов для вызова
methods = {
    "Левые прямоугольники": left_rectangles,
    "Правые прямоугольники": right_rectangles,
    "Средние прямоугольники": middle_rectangles,
    "Трапеции": trapezoidal,
    "Симпсон": simpsons
}

iterations = []
results = []

# Расчет количества итераций для каждого метода
for name, method in methods.items():
    count, result = calculate_iterations(method, a, b, tolerance)
    iterations.append(count)
    results.append(result)
    print(f"{name}: Итераций = {count}, Результат = {result:.6f}")

# Построение графика
plt.figure(figsize=(10, 6))
plt.bar(methods.keys(), iterations, color=['skyblue', 'lightgreen', 'lightcoral', 'gold', 'lightsalmon'])
plt.title("Сравнение количества итераций для разных методов")
plt.xlabel("Методы")
plt.ylabel("Количество итераций")
plt.xticks(rotation=15)
plt.tight_layout()
plt.show()
