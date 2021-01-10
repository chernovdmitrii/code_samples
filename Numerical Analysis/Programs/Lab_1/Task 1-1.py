import numpy as np
from scipy import integrate, misc
import matplotlib.pyplot as plt
import time

# ------------------------------------------------------------------------
# Вычислить интеграл   с помощью средств  Python

N = 25
# a = -5 + 0.1 * N
# b = 7 - 0.1 * N

a = 0
b = 3

# def f(x):
#     return abs(N * np.cos(2 ** x))

def f(x):
    return x ** 2

I_builtIn = integrate.quad(f, a, b)[0]

print('Machine: ', I_builtIn)
print('a: ', a)
print('b: ', b)

# ------------------------------------------------------------------------
# Построить график подынтегральной функции.
x = np.linspace(a, b, 100, endpoint=True)
err = np.zeros(100) + 10 ** (-8)
plt.grid(True)
plt.plot(x, err)
plt.plot(x, f(x), label="f(x)")
plt.legend()
plt.savefig("graph_1.png", dpi=500)
plt.show()

# ------------------------------------------------------------------------
# Составить программу, содержащую следующие разделы:
# а) вычисление интеграла по составным квадратурным формулам левых прямоугольников
# и индивидуального варианта с заданным шагом h;

h = 0.1


def leftRule(f, a, b, step):
    answer = 0
    n = int((b - a) / step)  # round up
    for i in range(0, n):
        answer += f(a + step * i) * step

    return answer


def midpointRule(f, a, b, step):
    answer = 0
    n = int((b - a) / step)
    for i in range(0, n):
        answer += f(a + step * (i + 0.5)) * step
    return answer


# I_left_rule = leftRule(f, a, b, h)
# I_mid_rule = midpointRule(f, a, b, h)
# print("Left rule: ", I_left_rule)
# print("Midpoint rule: ", I_mid_rule)

# б) вычисление значение интеграла с заданной точностью; оценку погрешности произво-дить на основе правила Рунге;
# c) вычисление уточненного значения интеграла (то есть выполнение уточнения по Рунге).


eps = 10 ** (-2)


x = np.linspace(a, b, 100, endpoint=True)
err = np.zeros(100) + 10 ** (-8)
plt.grid(True)
plt.plot(x, err)
plt.plot(x, f(x), label="f(x)")
plt.plot(x, misc.derivative(f, x, dx=1e-14, n=1), label="f'(x)")
plt.legend()
plt.savefig("graph_2.png", dpi=500)
plt.show()

x = np.linspace(a, b, 100, endpoint=True)
err = np.zeros(100) + 10 ** (-8)
plt.grid(True)
plt.plot(x, err)
plt.plot(x, f(x), label="f(x)")
plt.plot(x, misc.derivative(f, x, dx=1e-14, n=2), label="f''(x)")
plt.legend()
plt.savefig("graph_3.png", dpi=500)
plt.show()

def calculateStepLeftRule(f, a, b, eps):
    # Return evenly spaced values within a given interval (start, stop, step)
    divideX = np.arange(a, b, eps)
    derivatives = np.abs(misc.derivative(f, divideX, dx=1e-10, n=1))
    max_value = np.amax(derivatives)
    result = 2 * eps / ((b - a) * max_value)
    number = np.ceil((b - a) / result)
    result = (b - a) / number

    return result, number


def calculateStepMidpointRule(f, a, b, eps):
    # Return evenly spaced values within a given interval (start, stop, step)
    divideX = np.arange(a, b, eps)
    derivatives = np.abs(misc.derivative(f, divideX, dx=1e-6, n=2))
    max_value = np.amax(derivatives)
    result = np.sqrt(24 * eps / ((b - a) * max_value))
    number = np.ceil((b - a) / result)
    result = (b - a) / number

    return result, number


def RungeRule(I_h, I_hDiv2, p):
    return (I_h - I_hDiv2) / (2 ** p - 1)


def RungePrecision(I_h, I_hDiv2, p):
    return I_hDiv2 + (I_hDiv2 - I_h) / (2 ** p - 1)

#
# h_left, number_left = calculateStepLeftRule(f, a, b, eps)
#
# I_h_left = leftRule(f, a, b, h_left)
# I_hDive2_left = leftRule(f, a, b, h_left / 2)
#
# err_runge_left = RungeRule(I_h_left, I_hDive2_left, 1)
# prec_runge_left = RungePrecision(I_h_left, I_hDive2_left, 1)
#
# print('--------------Left Rule--------------')
# print('Number of divisions : ', number_left)
# print('Step                : ', h_left)
# print('Integral            : ', I_h_left)
# print('Runge error         : ', err_runge_left)
# print('Runge precision     : ', prec_runge_left)
# print('Left Rule Difference: ', abs(I_h_left - I_builtIn))
# print('Runge Difference    : ', abs(I_h_left - I_builtIn))
#
# h_mid, number_mid = calculateStepMidpointRule(f, a, b, eps)
#
# I_h_mid = midpointRule(f, a, b, h_mid)
# I_hDive2_mid = midpointRule(f, a, b, h_mid / 2)
#
# err_runge_mid = RungeRule(I_h_mid, I_hDive2_mid, 2)
# prec_runge_mid = RungePrecision(I_h_mid, I_hDive2_mid, 2)
#
# print('--------------Midpoint Rule--------------')
# print('Number of divisions     : ', number_mid)
# print('Step                    : ', h_mid)
# print('Integral                : ', I_h_mid)
# print('Runge error             : ', err_runge_mid)
# print('Midpoint Rule Difference: ', abs(I_h_mid - I_builtIn))
# print('Runge Difference        : ', abs(I_h_mid - I_builtIn))
# ------------------------------------------------------------------------
# Вычислить значение интеграла с предельно возможной точностью каждым методом. Для этого выполнить вычислительный
# эксперимент: задавая  последовательно значения равными, например, 10^-6,10^-7,…., найти предельную точность вычисления
# для инте-грала по формулам прямоугольников. Начиная с найденного предельного значения  , найти предельную точность
# вычисления  для интеграла по индивидуальному варранту. В каждом случае вычислить также реальную погрешность  R,
# используя значение интеграла. Оценить время, затраченное на работу программ.


eps_left = 10 ** (-2)
start_time = time.time()
h_left, number_left = calculateStepLeftRule(f, a, b, eps_left)
I_left = leftRule(f, a, b, h_left)
I_runge_left = RungePrecision(I_left, leftRule(f, a, b, h_left / 2), 1)
print('--------------Left Rule--------------')
print('Eps                : ', eps_left)
print('Step               : ', h_left)
print('Number of divisions: ', number_left)
print('Integral           : ', I_left)
print('Difference         : ', abs(I_left - I_builtIn))
print('Time               : ', time.time() - start_time)
print('Runge Precision    : ', I_runge_left)
print('Difference         : ', abs(I_runge_left - I_builtIn))


eps_left = 10 ** (-3)
start_time = time.time()
h_mid, number_mid = calculateStepMidpointRule(f, a, b, eps_left)
I_mid = midpointRule(f, a, b, h_mid)
I_runge_mid = RungePrecision(I_mid, midpointRule(f, a, b, h_mid / 2), 2)
print('--------------Midpoint Rule--------------')
print('Eps                : ', eps_left)
print('Step               : ', h_mid)
print('Number of divisions: ', number_mid)
print('Integral           : ', I_mid)
print('Difference         : ', abs(I_mid - I_builtIn))
print('Time               : ', time.time() - start_time)
print('Runge Precision    : ', I_runge_mid)
print('Difference         : ', abs(I_runge_mid - I_builtIn))