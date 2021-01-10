import numpy as np
from scipy import integrate

# ------------------------------------------------------------------------
# Вычислить интеграл индивидуального варианта по фомуле Гаусса с числом узлов 4.
# Сравнить полученный результат с результатами задачи  1.1.
N = 25
a = -5 + 0.1 * N
b = 7 - 0.1 * N


def f(x):
    return abs(N * np.cos(2 ** x))


t = np.array([- np.sqrt(3 / 7 + 2 / 35 * np.sqrt(30)),
              - np.sqrt(3 / 7 - 2 / 35 * np.sqrt(30)),
              np.sqrt(3 / 7 - 2 / 35 * np.sqrt(30)),
              np.sqrt(3 / 7 + 2 / 35 * np.sqrt(30))])

A = np.array([1 / 2 - np.sqrt(30) / 36,
              1 / 2 + np.sqrt(30) / 36,
              1 / 2 + np.sqrt(30) / 36,
              1 / 2 - np.sqrt(30) / 36])


def GaussMethod(f, a, b, t, A, Number):
    result = 0
    for i in range(0, Number):
        result += A[i] * f((a + b) / 2 + (b - a) * t[i] / 2)
    return result * ((b - a) / 2)


I_gauss = GaussMethod(f, a, b, t, A, 4)
I_builtIn = integrate.quad(f, a, b)[0]
print('Gauss Integral   : ', I_gauss)
print('Built-in Integral: ', I_builtIn)
print('Difference       : ', abs(I_builtIn - I_gauss))
