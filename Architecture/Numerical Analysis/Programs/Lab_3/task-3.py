import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# ==========================[Global Variables]=============================
a = 1
b = 3
eps = 10 ** (-2)

Ux0 = 0  # U[i][0]
U0y = 0  # U[0][j]
Uxb = 0  # U[i][N[2]]
Uay = 0  # U[N[1]][j]


# ==========================[Global Functions]=============================

def f(x, y):
    # sin⁡(2πx/1)sin⁡(2πy/3)
    return np.sin(2 * np.pi * x) * np.sin(2 * np.pi * y / 3)


def df(x, y):
    # (4π^2+4/9 π^2 )  sin⁡(2 π x)  sin⁡((2 π y)/3)
    return -(4 * (np.pi ** 2) + (4 * (np.pi ** 2) / 9)) * np.sin(2 * np.pi * x) * np.sin(2 * np.pi * y / 3)


def create_matrix(h1, h2):
    N1 = int(a / h1)
    N2 = int(b / h2)
    n = (N1 - 1) * (N2 - 1)
    A = np.zeros((n, n))

    x = np.linspace(0, a, N1 + 1)
    y = np.linspace(0, b, N2 + 1)

    for i in range(n):
        A[i, i] = -2 / (h1 ** 2) - 2 / (h2 ** 2)

        # under main diagonal
        if (i + 1) % (N1 - 1) != 0:
            A[i + 1][i] = 1 / h1 ** 2

        # above main diagonal
        if i % (N1 - 1) != 0:
            A[i - 1][i] = 1 / h1 ** 2

    for i in range(0, n - N1 + 1):
        # under N1-1
        A[i][i + N1 - 1] = 1 / h2 ** 2
        # above N1-1
        A[i + N1 - 1][i] = 1 / h2 ** 2

    B = np.zeros(n)
    # Pushing the solutions
    for i in range(0, n):
        B[i] = df(x[i % (N1 - 1) + 1], y[i // (N1 - 1) + 1])

    # first block (lower boundary): subtracting ux0 / h[2]^2
    for i in range(1, N1):
        B[i - 1] += -Ux0 / h2 ** 2

    # last block (upper boundary): subtracting uby / h[2]^2
    for i in range(n - (N1 - 1) - 1, n):
        B[i - 1] += -Uay / h1 ** 2

    # (right boundary): subtracting u0y / h[1]^2
    for i in range(1, n, N1 - 1):
        B[i - 1] += -Uay / h1 ** 2

    # (left boundary): subtracting u0y / h[2]^2
    for i in range(N1 - 1, n, N1 - 1):
        B[i - 1] += -Uxb / h2 ** 2

    return A, B


def make_z(solvee, h1, h2):
    N1 = int(a / h1)
    N2 = int(b / h2)

    z = np.zeros(((N2 - 1) + 2, (N1 - 1) + 2))
    solvee = solvee.reshape(((N2 - 1), (N1 - 1)))

    for i in range(1, (N2 - 1) + 1):
        for j in range(1, (N1 - 1) + 1):
            z[i][j] = solvee[i - 1][j - 1]

    for i in range(0, N1):
        z[0][i] = Ux0
        z[N2][i] = Uxb

    for i in range(0, N2):
        z[i][0] = U0y
        z[i][N1] = Uay

    return z

def runge(first, second):
    return np.amax(abs(first[:: 2, :: 2] - second) / 3)


# =============================[Task 3.3.1]================================
# Подготовить тестовый пример для решения задачи на прямоугольнике.

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(1, 1, 1, projection='3d')

x_axis = np.linspace(0, a, 100)
y_axis = np.linspace(0, b, 100)
x, y = np.meshgrid(x_axis, y_axis)
z = f(x, y)
ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap=cm.plasma)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Analytical solution')
plt.savefig("pic_3.1.png", dpi = 500)
plt.show()

# =============================[Task 3.3.2]================================
# Составить подпрограмму решения системы итерационным методом

h1 = 0.05
h2 = 0.05

mtr = create_matrix(h1, h2)

solvee = np.linalg.solve(mtr[0], mtr[1], )
z = make_z(solvee, h1, h2)

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(1, 1, 1, projection='3d')
x_axis = np.linspace(0, a, int(a / h1) + 1)
y_axis = np.linspace(0, b, int(b / h2) + 1)
x, y = np.meshgrid(x_axis, y_axis)
ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap=cm.plasma)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Built-in solution')
plt.savefig("pic_3.2.png", dpi = 500)
plt.show()


# =============================[Task 3.3.3]================================
# Решить задачу Дирихле в прямоугольнике индивидуальным методом с
# точностью 0.001. Для  оценки погрешности использовать правило Рунге.

def norma(x):
    sum = 0
    for i in x:
        sum += i ** 2
    return np.sqrt(sum)


def Generalized_minimal_residual_method(A, B):
    x_n1 = np.zeros(B.size)
    count = 0
    # eps = 10 ** (-3)
    global eps
    flag = True

    while True:
        x_n = x_n1  # zero vector

        # вычислить x^(n) и вектор навязки r^(n)= A * x^(n) - b

        r = A.dot(x_n1) - B
        if flag:
            r_0 = r
            flag = False

        # Вычисляется параметр tau[n+1] и  затем x^(n + 1)= x^(n) - tau[n+1] * r^(n)

        tau = (np.dot(np.dot(A, r), r)) / np.dot(np.dot(A, r), np.dot(A, r))
        x_n1 = x_n - tau * r

        # Вычисления ведутся до тех пор пока ||r^(n)|| / ||r^(0)||  <= eps, то есть первоначальная норма невязки
        # не уменьшится в eps^(-1) раз.

        if (norma(r) / norma(r_0)) <= eps:
            break
        count += 1

    return x_n1


h1 = 0.1
h2 = 0.1
N1 = int(a / h1)
N2 = int(b / h2)

mtr = create_matrix(h1, h2)

solvee = Generalized_minimal_residual_method(mtr[0], mtr[1])
z = make_z(solvee, h1, h2)

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(1, 1, 1, projection='3d')
x_axis = np.linspace(0, a, int(a / h1) + 1)
y_axis = np.linspace(0, b, int(b / h2) + 1)
x, y = np.meshgrid(x_axis, y_axis)
ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap=cm.plasma)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Generalized minimal residual method')
plt.savefig("pic_3.4.png", dpi = 500)
plt.show()


h1 = 0.1
h2 = 0.1
precisions = np.zeros(0)
answer_h = np.zeros((0, 0))
precision = 10

while (precision > eps):
    precisions = np.zeros(int(abs(a - b) / h1))
    a_2h, b_2h = create_matrix(h1, h2)
    solvee_loc = Generalized_minimal_residual_method(a_2h, b_2h)
    answer_2h = make_z(solvee_loc, h1, h2)

    h1 = h1 / 2
    h2 = h2 / 2

    a_2, b_2 = create_matrix(h1, h2)
    solvee_loc = Generalized_minimal_residual_method(a_2, b_2)
    answer_h = make_z(solvee_loc, h1, h2)


    precision = runge(answer_h, answer_2h)

print('Step   : ', h1)
print('Precise: ', precision)


z = answer_h

fig = plt.figure(figsize=(10, 10))  # создаём полотно для рисунка
ax = fig.add_subplot(1, 1, 1, projection='3d')
x_axis = np.linspace(0, a, int(a / h1) + 1)
y_axis = np.linspace(0, b, int(b / h2) + 1)
plt.xlabel("X")
plt.ylabel("Y")
# abss = abs(z - f(x_axis, y_axis))
x, y = np.meshgrid(x_axis, y_axis)
ax.plot_surface(x, y, z, rstride=1, cstride=1, cmap=cm.plasma)
plt.title('Step 10 ^ (-3 )')
plt.savefig("pic_3.5.png", dpi = 500)
plt.show()

# z = y_ans_h

fig = plt.figure(figsize=(10, 10))  # создаём полотно для рисунка
ax = fig.add_subplot(1, 1, 1, projection='3d')
x_axis = np.linspace(0, a, int(a / h1) + 1)
y_axis = np.linspace(0, b, int(b / h2) + 1)
plt.xlabel("X")
plt.ylabel("Y")
x, y = np.meshgrid(x_axis, y_axis)
ax.plot_surface(x, y, abs(z - f(x, y)), rstride=1, cstride=1, cmap=cm.plasma)
plt.title('Error')
plt.savefig("pic_3.6.png", dpi = 500)
plt.show()

# =============================[Task 3.3.4]================================
# # Решить задачу Дирихле в односвязной области.

# =============================[Task 3.3.5]================================
# Представить полученные результаты в виде таблиц и графиков поверхностей.
