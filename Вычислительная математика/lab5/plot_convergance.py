import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных из CSV-файла
data = pd.read_csv('convergence_data.csv')

# Построение графиков
plt.figure(figsize=(10, 6))
plt.plot(data['epsilon'], data['PowerMethod'], label="Степенной метод", marker='o')
plt.plot(data['epsilon'], data['ScalarProductMethod'], label="Метод скалярных произведений", marker='o')
plt.plot(data['epsilon'], data['RayleighQuotientMethod'], label="Метод частных Рэлея", marker='o')
plt.plot(data['epsilon'], data['InverseIterationMethod'], label="Обратные итерации", marker='o')

# Настройка осей
plt.xlabel('Точность (ε)')
plt.ylabel('Количество итераций')
plt.title('Зависимость количества итераций от точности для различных методов')
plt.legend()
plt.grid(True)

# Обратный логарифмический масштаб для оси X, чтобы значения отображались от 10^-3 до 10^-9
plt.xscale('log')
plt.gca().invert_xaxis()  # Инвертирование оси X

# Отображение графика
plt.show()
