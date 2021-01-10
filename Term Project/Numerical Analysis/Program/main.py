import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# ==========================[Global Variables]=============================

l = 3
T = 0.4
N1 = 100
N2 = 2000
h = l / N1
th = T / N2
quantity = 10

func1 = not True
func2 = not True
func3 = not True
func4 = not True
func5 =  True
func6 = not True

if func3:
    a = 1
else:
    a = 5

if func4:
    eps = 0.1 * l
    xi = l / 4

if func5:
    eps = 0.01 * l
    xi = l / 2

if func6:
    eps = 0.01 * l
    xi = l / 3

# ==========================[Global Functions]=============================

analytic = True
if func4 or func5 or func6:
    analytic = False


def analytical(x, t):
    if func1:
        return np.sin(3 * np.pi * x) * 5 * np.cos(15 * np.pi * t)
    if func2:
        return np.sin(4 * np.pi * x) * np.sin(20 * np.pi * t)
    if func3:
        return np.sin(2 * np.pi * x) * np.sin(2 * np.pi * t)
    if func4:
        return 0
    if func5:
        return 0
    if func6:
        return 0
    return -1


def f(x, t):
    if func1:
        return 0
    if func2:
        return 0
    if func3:
        return 0
    if func4:
        return 0
    if func5:
        return 0
    if func6:
        return 0
    return -1


# u(0,t) = μ[1](t)
def left(x):
    if func1:
        return 0
    if func2:
        return 0
    if func3:
        return 0
    if func4:
        return 0
    if func5:
        return 0
    if func6:
        return 0
    return -1


# u(l,t) = μ[2](t)
def right(x):
    if func1:
        return 0
    if func2:
        return 0
    if func3:
        return 0
    if func4:
        return 0
    if func5:
        return 0
    if func6:
        return 0
    return -1


# u(x,0) = ψ(x)
def bottom(x):
    if func1:
        return 5 * np.sin(3 * np.pi * x)
    if func2:
        return 0
    if func3:
        return 0
    if func4:
        if (xi - eps) <= x <= (xi + eps):
            return 2 * eps
        else:
            return 0
    if func5:
        if (xi - eps) <= x <= (xi + eps):
            return 2 * eps
        else:
            return 0
    if func6:
        if (xi - eps) <= x <= (xi + eps):
            return 2 * eps
        else:
            return 0
    return -1


# u[t](x,0) = φ(x)
def derivative(x):
    if func1:
        return 0
    if func2:
        return 20 * np.pi * np.sin(4 * np.pi * x)
    if func3:
        return 2 * np.pi * np.sin(2 * np.pi * x)
    if func4:
        return 0
    if func5:
        return 0
    if func6:
        return 0
    return -1


# ===========================[Main Functions]==============================

def diff_scheme():
    global a
    global l
    global T
    global h
    global th
    global N1
    global N2

    x = np.linspace(0, l, N1)
    t = np.linspace(0, T, N2)

    U = np.zeros((N2, N1))

    # filling bottom border
    for i in range(0, N1):
        U[0][i] = bottom(x[i])

    # filling left and right borders
    for j in range(0, N2):
        U[j][0] = left(t[j])
        U[j][N1 - 1] = right(t[j])

    # filling 1 row (the one with the derivative)
    for i in range(1, N1 - 1):
        U[1][i] = th * derivative(x[i]) + ((th ** 2) / 2) * (
                (a ** 2) * (U[0][i + 1] - 2 * U[0][i] + U[0][i - 1]) / (h ** 2) + f(x[i], t[i])) + U[0][i]

    # the rest of the matrix
    for j in range(1, N2 - 1):
        for i in range(1, N1 - 1):
            U[j + 1][i] = (th ** 2) * f(x[i], t[j]) + (
                    ((a ** 2) * (th ** 2) / (h ** 2)) * (U[j][i + 1] - 2 * U[j][i] + U[j][i - 1])) + 2 * U[j][i] - \
                          U[j - 1][i]

    return x, U


def printTable(data, name):
    _h = l / quantity
    _th = T / quantity
    tbl_step_h = int(N1 / quantity)
    tbl_step_th = int(N2 / quantity)

    margin = 13
    line = '+-------+'
    line += (('-' * margin) + '+') * (quantity + 1)
    divider_no = 9 + (margin + 1) * (quantity + 1) - 22
    divider_no = int(divider_no / 2)
    _name = '[{:>' + str(20) + '}]'
    divider = '=' * divider_no
    divider = divider + _name + divider

    step_t = 0
    step_x = 0

    # Creating a header
    head = []
    head_val = []
    head_string = '|{:>7}|'.format('t')

    for i in range(quantity + 1):
        head.append('u({}, t)'.format(round(step_x, 1)))
        step_x += _h

    for i in range(quantity + 1):
        head_val.append('{:>' + str(margin) + '}|')

    for i in range(quantity + 1):
        head_val[i] = head_val[i].format(head[i])

    for i in range(quantity + 1):
        head_string += head_val[i]

    # drawing the header

    print(divider.format(name))
    print(line)
    print(head_string)
    print(line)

    # filling left column and table
    _i = 0
    for i in range(quantity + 1):

        val = ['|{:>7}|'.format(round(step_t, 2))]
        val_string = ''
        for j in range(quantity + 1):
            val.append('{:>' + str(margin) + '}|')

        _j = 0
        for j in range(1, quantity + 2):
            val[j] = val[j].format(round(data[_i][_j], 7))
            if _j == 0:
                _j += tbl_step_h - 1
            else:
                _j += tbl_step_h

        for j in range(quantity + 2):
            val_string += val[j]

        print(val_string)
        print(line)
        step_t += _th

        if _i == 0:
            _i += tbl_step_th - 1
        else:
            _i += tbl_step_th


# =============================[diff_scheme]===============================
#
x, arr = diff_scheme()

moment = int(N2 / 2)
second_h = T / quantity
second_m = T / 2

plt.plot(x, arr[moment], color='black')
plt.legend()
plt.grid('True')
plt.title('Difference Scheme\nTime = {}'.format(second_m))
plt.savefig("pic_1.png", dpi=500)
plt.show()

# # ================================[String]=================================
second_step = int(N2 / quantity)
print(second_step)
count = 0
last = 0
for i in range(0, N2, second_step):
    plt.plot(x, arr[i], label="{}".format(count))
    count += 1
    last += second_h

plt.legend()
plt.grid('True')
plt.title('Difference Scheme\nTime: from 0 to {}; Step: {}'.format(round(last, 1), second_h))
plt.savefig("pic_2.png", dpi=500)
plt.show()

# =============================[Analytical]================================
if analytic:
    x_axis = np.linspace(0, l, N1)
    t_axis = np.linspace(0, T, N2)
    x, t = np.meshgrid(x_axis, t_axis)

    precise = analytical(x, t)

    plt.plot(x[moment], precise[moment], color='black')
    plt.legend()
    plt.grid('True')
    plt.title('Analytical Solution\nTime = {}'.format(second_m))
    plt.savefig("pic_3.png", dpi=500)
    plt.show()

# ==========================[Analytical Strings]===========================
if analytic:
    count = 0
    last = 0
    for i in range(0, N2, second_step):
        plt.plot(x[0], precise[i], label="{}".format(count))
        count += 1
        last += second_h

    plt.legend()
    plt.grid('True')
    plt.title('Analytical Solution\nTime: from 0 to {}; Step: {}'.format(round(last, 1), second_h))
    plt.savefig("pic_4.png", dpi=500)
    plt.show()

# ================================[Error1]=================================
if analytic:
    err = np.zeros(N2)

    plt.plot(x[moment], abs(arr - precise)[moment], color='black')
    plt.legend()
    plt.grid('True')
    plt.title('Error\nTime = {}'.format(second_m))
    plt.savefig("pic_5.png", dpi=500)
    plt.show()

# ================================[Error2]=================================
if analytic:
    count = 0
    last = 0
    for i in range(0, N2, second_step):
        plt.plot(x[0], abs(arr - precise)[i], label="{}".format(count))
        count += 1
        last += second_h

    plt.legend()
    plt.grid('True')
    plt.title('Error\nTime: from 0 to {}; Step: {}'.format(round(last, 1), second_h))
    plt.savefig("pic_6.png", dpi=500)
    plt.show()

# ================================[Error3]=================================
if analytic:
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(1, 1, 1, projection='3d')

    x_axis = np.linspace(0, l, N1)
    y_axis = np.linspace(0, T, N2)
    x, y = np.meshgrid(x_axis, y_axis)
    ax.plot_surface(x, y, abs(arr - precise), rstride=1, cstride=1, cmap=cm.plasma)
    plt.xlabel('x')
    plt.ylabel('t')
    plt.title('Error')
    plt.savefig("pic_7.png", dpi=500)
    plt.show()

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(1, 1, 1, projection='3d')

x_axis = np.linspace(0, l, N1)
y_axis = np.linspace(0, T, N2)
x, y = np.meshgrid(x_axis, y_axis)
ax.plot_surface(x, y, arr, rstride=1, cstride=1, cmap=cm.plasma)
plt.xlabel('x')
plt.ylabel('t')
plt.title('Difference Scheme')
plt.savefig("pic_8.png", dpi=500)
plt.show()

if analytic:
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(1, 1, 1, projection='3d')

    x_axis = np.linspace(0, l, N1)
    y_axis = np.linspace(0, T, N2)
    x, y = np.meshgrid(x_axis, y_axis)
    ax.plot_surface(x, y, precise, rstride=1, cstride=1, cmap=cm.plasma)
    plt.xlabel('x')
    plt.ylabel('t')
    plt.title('Analytical Solution')
    plt.savefig("pic_9.png", dpi=500)
    plt.show()
# ================================[Tables]==================================
if analytic:
    printTable(precise, 'Analytical Solution')

printTable(arr, 'Difference Scheme')
