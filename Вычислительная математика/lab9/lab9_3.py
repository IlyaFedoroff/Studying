import numpy as np
import tkinter as tk
from tkinter import ttk

# Функции для дифференцирования
def f(x):
    return (2 + x) / (pow(x,2) + 1)

# Первая производная разностями вперед
def first_derivative_forward(y, h):

    n = len(y)

    first_deriv_forward_table = np.full(n, np.nan)

    for i in range(0,n-1):
        first_deriv_forward_table[i] = (y[i+1] - y[i])/h


    return first_deriv_forward_table

# Первая производная разностями назад
def first_derivative_backward(y, h):
    n = len(y)  # количество узлов

    first_deriv_table_backward = np.full(n, np.nan)

    for i in range(1,n):
        first_deriv_table_backward[i] = (y[i] - y[i-1])/h


    return first_deriv_table_backward

# Первая производная с вторым порядком точности
def first_derivative_second_order(y, h):

    n = len(y)
    if n < 3:
        raise ValueError("Для вычисления производной второго порядка необходимо минимум 3 точки.")


    # Массив для хранения производных
    first_deriv_table_second_order = np.full(n, np.nan)

    # Первая точка (x_0)
    first_deriv_table_second_order[0] = (-3 * y[0] + 4 * y[1] - y[2]) / (2 * h)   # (-3y0+4y1-y2)/2h

    # Последняя точка (x_n)
    first_deriv_table_second_order[-1] = (y[-3] - 4 * y[-2] + 3 * y[-1]) / (2 * h)    # (yn-2 - 4yn-1 + 3yn)/2h

    # Внутренние точки

    for i in range (1, n-1):
        first_deriv_table_second_order[i] = (y[i+1] - y[i-1])/(2*h)    # (yi+1 - yi-1)/2h

    return first_deriv_table_second_order   # Возвращаем массив значений производных для каждой точки yi из y

# Вторая производная
def second_derivative(y, h):
    n = len(y)
    if n < 3:
        raise ValueError("Для вычисления второй производной необходимо минимум 3 точки.")

    # Создаем массив для хранения второй производной
    second_deriv_table = np.full(n, np.nan)

    # Внутренние точки
    for i in range(1,n-1):
        numerator = (y[i+1] - 2*y[i] + y[i-1])
        denominator = pow(h,2)
        second_deriv_table[i] = numerator/denominator

    return second_deriv_table

# Точная первая производная
def exact_first_derivative(x):
    n = len(x)

    exact_first_derivative_table = np.zeros(n)

    for i in range(0,n):
        numerator = -(pow(x[i],2) + 4*x[i] - 1) # числитель
        denominator = pow((pow(x[i],2) + 1),2)  # знаменатель
        #print(f"числитель: {numerator}")
        #print(f"знаменатель: {denominator}")
        exact_first_derivative_table[i] = numerator / denominator   # дробь   (x^2 + 4x-1)/(x^2+1)^2

    return exact_first_derivative_table

# Точная вторая производная
def exact_second_derivative(x):
    n = len(x)
    exact_second_derivative_table = [0]*n

    for i in range(0,n):
        numerator = 2 * (pow(x[i],3) + 6*pow(x[i],2) - 3*x[i] - 2)
        denominator =   pow((pow(x[i],2) + 1),3)
        exact_second_derivative_table[i] = numerator / denominator

    return exact_second_derivative_table

# аналитическая третья производная
def exact_third_derivative(x):
    n = len(x)
    exact_third_derivative_table = np.full(n, np.nan)

    for i in range(0,n):
        numerator = 6*(x[i]**4 + 8*x[i]**3 - 6*x[i]**2 - 8*x[i] +1)
        denominator = (x[i]**2 + 1)**4
        exact_third_derivative_table[i] = -numerator/denominator

    return exact_third_derivative_table

# аналитическая четвертая производная
def exact_forth_derivative(x):
    n = len(x)
    exact_forth_derivative_table = np.full(n, np.nan)

    for i in range(0,n):
        numerator = 24*(x**5 + 10*x**4 - 10*x**3 - 20*x**2 + 5*x + 2)
        denominator = (x**2 + 1)**5
        exact_forth_derivative_table = numerator/denominator

    return exact_forth_derivative_table

# Значения x
x_values = np.array([0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1])
# Значения y
#y_values = np.array([2.000, 2.010, 2.019, 2.028, 2.037, 2.045, 2.053, 2.060, 2.067, 2.073, 2.079])
y_values = [f(x) for x in x_values]  # Табличные значения функции
h = x_values[1] - x_values[0]

# вычисление массивов
first_deriv_forward = first_derivative_forward(y_values, h)     # Первая производная вперед
first_deriv_backward = first_derivative_backward(y_values, h)   # Первая производная назад
first_deriv_second_order = first_derivative_second_order(y_values, h)   # Первая производная второго порядка
second_deriv = second_derivative(y_values, h)       # Вторая производная
exact_first_deriv = exact_first_derivative(x_values)     # Точная первая производная
exact_second_deriv = exact_second_derivative(x_values)   # Точная вторая производная


def calc_error(a, b):
    n1 = len(a)
    n2 = len(b)
    if (n1!=n2):
        print("error")
        return None
    res=[0]*n1
    for i in range(0,n1):
        res[i]=np.abs(a[i]-b[i])
    #print(f"массив погрешностей: {res}")
    max_err=np.max(res)

    #print(f"maxerror: {max_err}")
    return max_err


# теоретическая погрешность для первой производной
def theory_error_first_deriv():
    x = x_values
    n = len(x)
    res_deriv = np.full(n, np.nan)
    max_deriv = -10
    second_deriv = exact_second_deriv

    for i in range(0,n):
        result = np.abs((second_deriv[i]/2)*np.abs(h))
        if result > max_deriv:
            max_deriv = result
        res_deriv[i] = result   # сохраняем в массив (возможно не нужен)

    #print(f"res_deriv: {res_deriv}")
    return res_deriv


# теоретическая погрешность первой производной второго порядка
def theory_error_first_deriv_second_order():
    n = len(x_values)

    third_deriv = exact_third_derivative(x_values)
    res_deriv = np.full(n, np.nan)

    for i in range(0,n):
        res = third_deriv[i]/6
        res = res * np.abs(h**2)
        res_deriv[i] = np.abs(res)
    #print(f"теор: {res_deriv}")
    return res_deriv

# теоретическая погрешность второй производной
def theory_error_second_deriv():
    n = len(x_values)

    forth_deriv = exact_forth_derivative(x_values)
    res_deriv = np.full(n, np.nan)

    for i in range(0, n):
        res_deriv[i] = np.abs((forth_deriv[i]/12) * np.abs(h**2))

    #print(f"проверка : {res_deriv}")
    return res_deriv

# вернуть максимальную производную
def get_max_first_deriv():
    derivatives = np.abs(exact_first_deriv)
    return np.max(derivatives)

def get_max_second_deriv():
    derivatives = np.abs(exact_second_deriv)
    return np.max(derivatives)

def get_max_third_deriv():
    derivatives = np.abs(exact_third_derivative(x_values))
    return np.max(derivatives)

def get_max_forth_deriv():
    derivatives = np.abs(exact_forth_derivative(x_values))
    return np.max(derivatives)

# функции подсчета максимальной |E|
def get_max_theory_error_first_deriv():
    max_deriv = get_max_first_deriv()
    result = np.abs((max_deriv/2)*np.abs(h))
    return result

def get_max_theory_error_first_deriv_second_order():
    max_deriv = get_max_third_deriv()
    res = max_deriv/6
    res = res * np.abs(h**2)
    return np.abs(res)

def get_max_theory_error_second_deriv():
    max_deriv = get_max_forth_deriv()
    return np.abs((max_deriv/12) * np.abs(h**2))


# Оценка погрешностей
# погрешность для первой производной разностями вперед
new_first_deriv_arr_forw = first_deriv_forward[:-1]    # убираем последнюю точку
new_exact_first_deriv_arr_forw = exact_first_deriv[:-1]      # для массива с точными производными
error_first_deriv_forward = calc_error(new_first_deriv_arr_forw, new_exact_first_deriv_arr_forw)
theory_error_first_deriv_forward = theory_error_first_deriv()
max_theory_error_first_deriv_forward = get_max_theory_error_first_deriv()

# погрешность для первой производной разностями назад
new_first_deriv_arr_back = first_deriv_backward[1:] # Убираем первый элемент
new_exact_first_deriv_arr_back = exact_first_deriv[1:]
error_first_deriv_backward = calc_error(new_first_deriv_arr_back, new_exact_first_deriv_arr_back)
theory_error_first_deriv_backward = theory_error_first_deriv()
max_theory_error_first_deriv_backward = get_max_theory_error_first_deriv()

# погрешность для первой производной второго порядка
error_first_deriv_second_order = calc_error(first_deriv_second_order, exact_first_deriv)    # Абсолютная погрешность
theory_error_first_deriv_second_order = theory_error_first_deriv_second_order() # Теоретическая погрешность
max_theory_error_first_deriv_second_order = get_max_theory_error_first_deriv_second_order()

# погрешность для второй производной
new_second_deriv_arr = second_deriv[1:-1]   # убираем первую и последнюю точки
new_exact_second_deriv_arr = exact_second_deriv[1:-1]
error_second_deriv = calc_error(new_second_deriv_arr, new_exact_second_deriv_arr)
theory_error_second_deriv = theory_error_second_deriv() # Теоретическая погрешность
max_theory_error_second_deriv = get_max_theory_error_second_deriv()





# отладка
#print(f"вторая производная разностями: {second_deriv}")
#print(f"точная вторая производная: {exact_second_deriv}")


# Создание окна tkinter
root = tk.Tk()
root.title("Результаты вычислений производных")

# Добавление стилей
style = ttk.Style()
style.configure("Treeview", font=("Times New Roman", 14))
style.configure("Treeview.Heading", font=("Times New Roman", 16, "bold"))

# Создание вкладок
notebook = ttk.Notebook(root)
notebook.pack(fill=tk.BOTH, expand=True)

# Создание таблиц
frames = {}
trees = {}
columns = {
    "forward": ("i", "x_i", "y_i", "y'_i", "Точное y'_i", "|E_i|"),
    "backward": ("i", "x_i", "y_i", "y'_i", "Точное y'_i", "|E_i|"),
    "second_order": ("i", "x_i", "y_i", "y'_i", "Точное y'_i", "|E_i|"),
    "second": ("i", "x_i", "y_i", "y''_i", "Точное y''_i", "|E_i|")
}

# Первая производная (разность вперед)
frames["forward"] = ttk.Frame(notebook)
notebook.add(frames["forward"], text="Первая производная (1-й порядок)")
trees["forward"] = ttk.Treeview(frames["forward"], columns=columns["forward"], show="headings")
trees["forward"].pack(fill=tk.BOTH, expand=True)

# Первая производная (разность назад)
frames["backward"] = ttk.Frame(notebook)
notebook.add(frames["backward"], text="Первая производная (разность назад)")
trees["backward"] = ttk.Treeview(frames["backward"], columns=columns["backward"], show="headings")
trees["backward"].pack(fill=tk.BOTH, expand=True)

# Первая производная (второй порядок точности)
frames["second_order"] = ttk.Frame(notebook)
notebook.add(frames["second_order"], text="Первая производная (2-й порядок)")
trees["second_order"] = ttk.Treeview(frames["second_order"], columns=columns["second_order"], show="headings")
trees["second_order"].pack(fill=tk.BOTH, expand=True)

# Вторая производная
frames["second"] = ttk.Frame(notebook)
notebook.add(frames["second"], text="Вторая производная")
trees["second"] = ttk.Treeview(frames["second"], columns=columns["second"], show="headings")
trees["second"].pack(fill=tk.BOTH, expand=True)

# Настройка заголовков таблиц
for key, tree in trees.items():
    for col in columns[key]:
        tree.heading(col, text=col)

# Заполнение таблиц
for i in range(len(x_values)):
    trees["forward"].insert("", tk.END, values=(
        i,
        f"{x_values[i]:.2f}",
        f"{y_values[i]:.4f}",
        f"{first_deriv_forward[i]:.4f}",
        f"{exact_first_deriv[i]:.4f}",
        f"{theory_error_first_deriv_forward[i]:.9f}"
    ))


for i in range(len(x_values)):
    trees["backward"].insert("", tk.END, values=(
        i,
        f"{x_values[i]:.2f}",
        f"{y_values[i]:.4f}",
        f"{first_deriv_backward[i]:.4f}",
        f"{exact_first_deriv[i]:.4f}",
        f"{theory_error_first_deriv_backward[i]:.9f}"
    ))


for i in range(len(x_values)):
    trees["second_order"].insert("", tk.END, values=(
        i,
        f"{x_values[i]:.2f}",
        f"{y_values[i]:.4f}",
        f"{first_deriv_second_order[i]:.4f}",
        f"{exact_first_deriv[i]:.4f}",
        f"{theory_error_first_deriv_second_order[i]:.9f}"
    ))

for i in range(len(x_values)):
    trees["second"].insert("", tk.END, values=(
        i,
        f"{x_values[i]:.2f}",
        f"{y_values[i]:.4f}",
        f"{second_deriv[i]:.4f}",
        f"{exact_second_deriv[i]:.4f}",
        f"{theory_error_second_deriv[i]:.9f}"
    ))



# Отображение погрешностей
frame_errors = ttk.Frame(root)
frame_errors.pack(fill=tk.BOTH, expand=False, pady=10)

error_label = tk.Label(frame_errors, text=(
    f"Абсолютная                                   Теоретическая\n"
    f"разность вперед: {error_first_deriv_forward:.9f} | "
    f" {max_theory_error_first_deriv_forward:.9f}\n"
    f"разности назад: {error_first_deriv_backward:.9f} | "
    f" {max_theory_error_first_deriv_backward:.9f}\n"
    f"второго порядка: {error_first_deriv_second_order:.9f} | "
    f" {max_theory_error_first_deriv_second_order:.9f}\n"
    f"второй производной: {error_second_deriv:.9f} | "
    f" {max_theory_error_second_deriv:.9f}\n"
), justify=tk.LEFT, font=("Arial", 12))
error_label.pack()

# Запуск приложения
root.mainloop()
