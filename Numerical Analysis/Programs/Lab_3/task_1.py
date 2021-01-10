import numpy as np
import matplotlib.pyplot as plt

# ==========================[Global Variables]=============================
eps = 10 ** (-3)

a = 0
b = 3
p = -2
q = 3
ua = 2
ub = -4


# ==========================[Global Functions]=============================

def analytical(x):
    return (-(679 * np.exp(9) - 148) / (27 * (np.exp(12) - 1))) * np.exp(x) + (
            -(148 * np.exp(12) - 679 * np.exp(9)) / (27 * (np.exp(12) - 1))) * np.exp(
        -3 * x) - 1 / 3 * x ** 2 + 50 / 9 * x + 202 / 27


def f(x):
    return -x ** 2 + 18 * x + 12


def Runge(first, second, p):
    return abs((first - second) / ((2 ** p) - 1))


def diff_scheme_a(_h):
    n = int(abs(a - b) / _h)
    _a = np.full(n, (- 1 / (_h ** 2) - p / (2 * _h)))
    _b = np.full(n, (2 / (_h ** 2) + q))
    _c = np.full(n, (- 1 / (_h ** 2) + p / (2 * _h)))

    _a[0] = 0
    _a[n - 1] = 0
    _b[0] = 1
    _b[n - 1] = 1
    _c[0] = 0
    _c[n - 1] = 0

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


# ==============================[Task 3.1.2]=================================
# Найти приближенное решение задачи с точностью  0.001.
h = 0.5
precision = 10
answer_h = np.zeros(0)
count = 0
precisions = np.zeros(0)

while (precision > eps):
    precisions = np.zeros(int(abs(a - b) / h))
    # answer_2hh = np.linalg.solve(diff_scheme_a(h)[3], diff_scheme_b(f, h))
    answer_2h = solution(diff_scheme_a(h), diff_scheme_b(f, h))
    h = h / 2
    # answer_h = np.linalg.solve(diff_scheme_a(h), diff_scheme_b(f, h))
    answer_x = diff_scheme_b(f, h)
    answer_h = solution(diff_scheme_a(h), answer_x)
    for i in range(precisions.size):
        precisions[i] = Runge(answer_h[i * 2], answer_2h[i], 2)

    precision = np.max(precisions)
    count += 1

print('==========[Task 1.2]==========')
print('Precision given:', eps)
print('Precision local:', precision)
print('Number of dots :', int(abs(a - b) / h))
print('Step           :', h)
print('Interations    :', count)

# ==============================[Task 3.1.3]=================================
# На одном чертеже построить  графики приближенного и аналитического  решения
# задачи. Отдельно построить график погрешности.

# x = np.arange(a, b, h)
x  = np.linspace(a, b, int(abs(a - b) / h))
plt.plot(x, answer_h, label="Analytical", color='black')
plt.plot(x, analytical(x), ls=':', label="Approximate", color='magenta')
plt.legend()
plt.grid('True')
plt.savefig("pic_1.png", dpi = 500)
plt.show()

# x = np.arange(a, b, h)
plt.plot(x, answer_h - analytical(x), label="Error", color='blue')
# plt.plot(x, precisions, label="Error", color='blue')
plt.legend()
plt.grid('True')
plt.savefig("pic_2.png", dpi = 500)
plt.show()
