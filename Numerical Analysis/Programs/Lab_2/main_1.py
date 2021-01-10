import numpy as np
import matplotlib.pyplot as plt

# ==========================[Global Variables]=============================
eps = 10 ** (-6)

t = t0 = 0
T = 1.5
y0 = 2

h = (T - t0) / 10


# ==========================[Global Functions]=============================

def f(y, t):
    return -30 * y - 15 * (t ** 2) * np.sin(t) + (t ** 3) + 5


def Euler(y, t, h, f):
    return y + h * f(y, t)


def EulerCalculation(t, h, f, y, T):
    x = np.arange(t, T + h, h)
    quantity = x.size
    prev = y
    array = np.zeros(quantity)
    array[0] = y

    for i in range(0, quantity - 1):
        prev = Euler(prev, t, h, f)
        t += h
        array[i + 1] = prev

    return array, x


def Runge(first, second, p):
    return abs((first - second) / ((2 ** p) - 1))


# ==============================[Task 1.1]=================================
# Методом Эйлера  с постоянным шагом   найти  решение задачи Коши.
# Построить график решения

first, x1 = EulerCalculation(t, h, f, y0, T)

x = np.linspace(t, T + h, 100, endpoint=True)
plt.plot(x1, first, ls='--', label="Euler", color='magenta')
plt.legend()
plt.grid('True')
plt.savefig("pic_1.png", dpi=500)
plt.show()

# ==============================[Task 1.2]=================================
# Cоставить  программу вычисления  решения  методом Эйлера с  заданной
# точностью, используя правило Рунге. Найти решение задачи с точностью
# eps = 10 ** (-8), число точек N и шаг, при котором точность достигается.
# Построить график решения.

precise = 1.0
h = (T - t0) / 10

euler_h = np.zeros(0)
euler_h_div_2 = np.zeros(0)
number_h = 0
number_h_div_2 = 0
count = 0

while (precise >= eps):
    euler_h, number_h = EulerCalculation(t, h, f, y0, T)
    h = h / 2
    euler_h_div_2, number_h_div_2 = EulerCalculation(t, h, f, y0, T)
    precision = np.zeros(number_h.size)

    for i in range(0, number_h.size - 1):
        precision[i] = Runge(euler_h_div_2[i * 2], euler_h[i], 1)

    precise = np.amax(precision)

    count += 1

print('==========[Task 1.2]==========')
print('Precision     :', precise)
print('Number of dots:', number_h_div_2.size)
print('Step          :', h)
print('N             :', count)

x = np.linspace(t, 6, 100, endpoint=True)
plt.plot(number_h_div_2, euler_h_div_2, ls='--', label="Euler", color='magenta')
plt.legend()
plt.grid('True')
plt.savefig("pic_2.png", dpi = 500)
plt.show()


# ==============================[Task 1.2]=================================
# Составить  программу вычисления  решения с  заданной точностью методом
# индивидуального варианта. Найти решение задачи с заданной точностью,
# число точек N  и шаг, при котором точность достигается.
# Построить график решения задачи.
#
# Метод разложения по Тейлору 2-го порядка

def dt(y, t):
    return 3 * t * (t - 5 * t * np.cos(t) - 10 * np.sin(t))

def dy(y, t):
    return -30


def Taylor(y0, t0, h, f):
    return y0 + h * f(y0, t0) + ((h ** 2) / 2) * (dt(y0, t0) + dy(y0, t0) * f(y0, t0))


def TaylorCalculate(y0, t0, h, f, T):
    x = np.arange(t0, T + h, h)
    quantity = x.size
    prev = y0
    array = np.zeros(quantity)
    array[0] = y0

    for i in range(0, quantity - 1):
        prev = Taylor(prev, t0, h, f)
        t0 += h
        array[i + 1] = prev

    return array, x


t = t0 = 0
T = 1.5
h = (T - t0) / 10
y0 = 2

taylor_h = np.zeros(0)
taylor_h_div_2 = np.zeros(0)
number_h_t = 0
number_h_div_2_t = 0
precise = 1.0
count = 0

while (precise >= eps):
    taylor_h, number_h_t = TaylorCalculate(y0, t0, h, f, T)
    h = h / 2
    taylor_h_div_2, number_h_div_2_t = TaylorCalculate(y0, t0, h, f, T)
    precision = np.zeros(number_h_t.size)

    for i in range(0, number_h_t.size - 1):
        precision[i] = Runge(taylor_h_div_2[i * 2], taylor_h[i], 2)

    precise = np.amax(precision)

    count += 1

print('==========[Task 1.3]==========')
print('Precision     :', precise)
print('Number of dots:', number_h_div_2_t.size)
print('Step          :', h)
print('N             :', count)

t = t0 = 0
T = 1.5

x = np.linspace(t, T + (T - t0) / 10, 100, endpoint=True)
plt.plot(number_h_div_2_t, taylor_h_div_2, label="Taylor", color='black')
plt.plot(number_h_div_2, euler_h_div_2, ls=':', label="Euler", color='magenta')
plt.legend()
plt.grid('True')
plt.savefig("pic_3.png", dpi = 500)
plt.show()
