import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# =========================================================================
# Используя программу задачи  2.1. , найти решения задач  Коши  для  ОДУ
# 1 порядка (2.1) и (2.2)  на отрезке   с заданной точностью .  Построить
# графики решений и найти наибольшую площадь, заключенную между интегральными
# кривыми.
# (2.1) y' = k(A - y)(y - B)              ; y(0) = y[0]
# (2.2) y' = k(A - z)(z - B) - C*sin(t/w) ; z(0) = z[0] = y[0]


# ==========================[Global Variables]=============================

y0 = 58
T = 40
A = 60
B = 18
C = 3
w = 3
K = 0.04
t0 = 0

eps = 10 ** (-8)


# ==========================[Global Functions]=============================

def f1(y, t):
    return K * (A - y) * (y - B)


def f2(z, t):
    return K * (A - z) * (z - B) - C * np.sin(t / w)


def Runge(first, second, p):
    return abs((first - second) / ((2 ** p) - 1))


def Taylor(y0, t0, h, f, dt, dy):
    return y0 + h * f(y0, t0) + ((h ** 2) / 2) * (dt(y0, t0) + dy(y0, t0) * f(y0, t0))


def TaylorCalculate(y0, t0, h, f, T, dt, dy):
    x = np.arange(t0, T + h, h)
    quantity = x.size
    prev = y0
    array = np.zeros(quantity)
    array[0] = y0

    for i in range(0, quantity - 1):
        prev = Taylor(prev, t0, h, f, dt, dy)
        t0 += h
        array[i + 1] = prev

    return array, x


# ==============================[Task 2.2]=================================
# Найти  приближенные решения задач (2.1) и (2.2).
# Построить графики полученных решений y(t) и z(t).

def dt_f1(y, t):
    return 0


def dy_f1(y, t):
    return 3.12 - 0.08 * y


def dt_f2(z, t):
    return -np.cos(t / 3)


def dy_f2(z, t):
    return 3.12 - 0.08 * z


h = 0.1

first = np.zeros(0)
first_h_div_2 = np.zeros(0)

first_num = 0
first_num_div_2 = 0
precise = 1.0

while (precise >= eps):
    first, first_num = TaylorCalculate(y0, t0, h, f1, T, dt_f1, dy_f1)
    h = h / 2
    first_h_div_2, first_num_div_2 = TaylorCalculate(y0, t0, h, f1, T, dt_f1, dy_f1)
    precision = np.zeros(first_num.size)

    for i in range(0, first_num.size - 1):
        precision[i] = Runge(first_h_div_2[i * 2], first[i], 2)

    precise = np.amax(precision)


print('==========[Task 2.2]==========')
print('Precision     :', precise)
print('Number of dots:', first_num_div_2.size)
print('Step          :', h)


second = np.zeros(0)
second_h_div_2 = np.zeros(0)

second_num = 0
second_num_div_2 = 0
precise = 1.0
h = 0.1

while (precise >= eps):
    second, second_num = TaylorCalculate(y0, t0, h, f2, T, dt_f2, dy_f2)
    h = h / 2
    second_h_div_2, second_num_div_2 = TaylorCalculate(y0, t0, h, f2, T, dt_f2, dy_f2)
    precision = np.zeros(second_num.size)

    for i in range(0, second_num.size - 1):
        precision[i] = Runge(second_h_div_2[i * 2], second[i], 2)

    precise = np.amax(precision)

print('==========[Task 2.2]==========')
print('Precision     :', precise)
print('Number of dots:', second_num_div_2.size)
print('Step          :', h)

x = np.linspace(t0, T + 1, 100, endpoint=True)
plt.plot(first_num_div_2, first_h_div_2, label="y(t)", color='black')
plt.plot(second_num_div_2, second_h_div_2, ls=':', label="z(t)", color='magenta')
plt.legend()
plt.grid('True')
plt.savefig("pic_4.png", dpi = 500)
plt.show()

x_plot = np.linspace(0, T, 100)

solution_1 = odeint(f1, y0, x_plot)
solution_2 = odeint(f2, y0, x_plot)

plt.plot(x_plot, solution_1, ls='-', label='y(t)')
plt.plot(x_plot, solution_2, ls=':', label='z(t)')
plt.legend()
plt.grid('True')
plt.savefig("pic_5.png", dpi = 500)
plt.show()

# ==============================[Task 2.3]=================================
# Вычислить приближенно площади между полученными кривыми на отрезке
# по квадратурной формуле индивидуального варианта ЛР 1

y_dots = np.zeros(0)
x_dots = np.zeros(0)
x_indexes = []
count = 0

# Находим точки пересечения

difference = first_h_div_2 - second_h_div_2
# True = -1 ; False = 1
sign = True

for i in range(1, difference.size):
    if difference[i] > 0 and sign:
        y_dots = np.append(y_dots, first_h_div_2[i])
        x_dots = np.append(x_dots, first_num_div_2[i])
        x_indexes.append(i)
        count += 1
        sign = False

    if difference[i] < 0 and not sign:
        y_dots = np.append(y_dots, first_h_div_2[i])
        x_dots = np.append(x_dots, first_num_div_2[i])
        x_indexes.append(i)
        count += 1
        sign = True

print('==========[Task 2.3]==========')
print('Number of intersections: ', count)
print('y axis coordinates     :', y_dots)
print('x axis coordinates     :', x_dots)
print('Indexes                :', x_indexes)


# Правило центральных треугольников
#
# def midpointRule(f, a, b, step):
#     answer = 0
#     n = int((b - a) / step)
#     for i in range(0, n):
#         answer += f(a + step * (i + 0.5)) * step
#     return answer

def midpointRule(y, a, b, step, start, end):
    answer = 0
    n = int((b - a) / step)
    for i in range(start + 1, end):
        answer += (y[i - 1] + y[i]) / 2
    return answer * step


areas = np.zeros(0)

for i in range(1, x_dots.size):
    one = midpointRule(first_h_div_2, x_dots[i - 1], x_dots[i], h, x_indexes[i - 1], x_indexes[i])
    two = midpointRule(second_h_div_2, x_dots[i - 1], x_dots[i], h, x_indexes[i - 1], x_indexes[i])

    areas = np.append(areas, abs(one - two))

print('==========[Max Area]==========')
print('Areas     :', areas)
print('Max. area :',np.amax(areas))
