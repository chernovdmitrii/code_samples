import numpy as np
import matplotlib.pyplot as plt

# ==========================[Global Variables]=============================
eps = 10 ** (-3)

a = 0
b = 3
q = 3
x0 = 2.7
ua = 6
ub = 2

colors = ['blue', 'black', 'magenta', 'cyan', 'red', 'green', 'yellow']


# ==========================[Global Functions]=============================

def f(x):
    return -x ** 2 + 18 * x + 12


def k1(x):
    return  1 # 10 - 3 * x


def k2(x):
    return 100 # 3 * x + 2


def k3(x):
    return 1000 # 2 + np.sqrt(3 * x)


def Runge(first, second, p):
    return abs((first - second) / ((2 ** p) - 1))


def solution(data, F):
    a = data[0]
    b = data[1]
    c = data[2]
    answer = np.zeros(F.size)
    alpha = [-c[0] / b[0]]
    beta = [F[0] / b[0]]
    n = len(F)

    for i in range(1, n):
        alpha.append(-c[i] / (a[i] * alpha[i - 1] + b[i]))
        beta.append((F[i] - a[i] * beta[i - 1]) / (a[i] * alpha[i - 1] + b[i]))

    answer[n - 1] = beta[n - 1]

    for i in range(n - 1, 0, -1):
        answer[i - 1] = alpha[i - 1] * answer[i] + beta[i - 1]

    return answer


# ==============================[Task 3.2.1]=================================
# Составить подпрограмму, вычисляющую функцию k(x) из индивидуального
# варианта.

def K(x, first, second, third):
    if 0 <= x <= 1:
        return first(x)
    if 1 < x <= 2:
        return second(x)
    if 2 < x <= 3:
        return third(x)

    # Error handling
    return -1


# ==============================[Task 3.2.2]=================================
# Найти приближенное решение задачи с точностью 0.001, модифицируя
# разностную схему из  задачи 3.1.

def diff_scheme_a(_h, first, second, third):
    n = int(abs(a - b) / _h)
    x = np.arange(a, b, h)

    _a = np.zeros(n)
    _b = np.zeros(n)
    _c = np.zeros(n)
    _a[0] = 0
    _a[n - 1] = 0
    _b[0] = 1
    _b[n - 1] = 1
    _c[0] = 0
    _c[n - 1] = 0

    for i in range(1, n - 1):
        _a[i] = -K(x[i] - _h / 2, first, second, third) / _h ** 2
        _b[i] = (K(x[i] - _h / 2, first, second, third) + K(x[i] + _h / 2, first, second, third)) / _h ** 2 + q
        _c[i] = -K(x[i] + _h / 2, first, second, third) / _h ** 2

    return _a, _b, _c


def diff_scheme_b(_f, _h):
    x = np.arange(a, b, _h)
    n = x.size
    matrix = np.zeros(n)
    matrix[0] = ua
    matrix[n - 1] = ub

    for i in range(1, n - 1):
        matrix[i] = _f(x[i])

    return matrix


h = 0.5
precision = 10
answer_h = np.zeros(0)
count = 0

# while (precision > eps):
#     precisions = np.zeros(int(abs(a - b) / h))
#     answer_2h = solution(diff_scheme_a(h, k1, k2, k3), diff_scheme_b(f, h))
#     h = h / 2
#     answer_x = diff_scheme_b(f, h)
#     answer_h = solution(diff_scheme_a(h, k1, k2, k3), answer_x)
#     for i in range(precisions.size):
#         precisions[i] = Runge(answer_h[i * 2], answer_2h[i], 2)
#
#     precision = np.max(precisions)
#     count += 1
#
# print('==========[Task 1.2]==========')
# print('Precision given:', eps)
# print('Precision local:', precision)
# print('Number of dots :', int(abs(a - b) / h))
# print('Step           :', h)
# print('Interations    :', count)

# ==============================[Task 3.2.3]=================================
# Для каждого варианта конфигурации стержня произвести  расчет по разностной
# схеме.
h = 10 ** (-2)
num = int(abs(a - b) / h)

samples = np.zeros((6, num))

samples[0] = solution(diff_scheme_a(h, k1, k2, k3), diff_scheme_b(f, h))
samples[1] = solution(diff_scheme_a(h, k1, k3, k2), diff_scheme_b(f, h))
samples[2] = solution(diff_scheme_a(h, k2, k1, k3), diff_scheme_b(f, h))
samples[3] = solution(diff_scheme_a(h, k2, k3, k1), diff_scheme_b(f, h))
samples[4] = solution(diff_scheme_a(h, k3, k1, k2), diff_scheme_b(f, h))
samples[5] = solution(diff_scheme_a(h, k3, k2, k1), diff_scheme_b(f, h))

# ==============================[Task 3.2.3]=================================
# Построить на одном чертеже графики приближенного решения для каждой
# конфигурации стержня.

maximum = np.max(samples)
minimum = np.min(samples)

x_dot = np.full(num, x0)
y_dot = np.linspace(minimum, maximum, num)

x = np.arange(a, b, h)
plt.plot(x, samples[0], label="123", color=colors[0])
plt.plot(x, samples[1], label="132", color=colors[1])
plt.plot(x, samples[2], label="213", color=colors[2])
plt.plot(x, samples[3], label="231", color=colors[3])
plt.plot(x, samples[4], label="312", color=colors[4])
plt.plot(x, samples[5], label="321", color=colors[5])
plt.plot(x_dot, y_dot, label="dot", color=colors[6])
plt.legend()
plt.grid('True')
plt.savefig("pic_3.png", dpi = 500)
plt.show()
