import numpy as np

def f(y, t):
    return y * (np.cos(t) / np.sin(t)) + (np.sin(t) ** 2)

def Euler(y, t, h, f):
    return y + h * f(y, t)

h = 0.2
t = np.pi / 2
prev = 0.0

first = np.zeros(7)
first[0] = 0.0

for i in range(0, 6):
    prev = round(Euler(prev, t, h, f), 6)
    print(i+1, ':', prev)
    t += h
    first[i + 1] = prev

print('-----------------------------------------')

h = 0.4
t = np.pi / 2
prev = 0.0

second = np.zeros(7)
second[0] = 0.0

for i in range(0, 3):
    prev = round(Euler(prev, t, h, f), 6)
    print(i+1, ':', prev)
    t += h
    second[i + 1] = prev

print('-----------------------------------------')


def Runge(first, second):
    return round(abs((first - second) / (2 ** 1 - 1)), 6)

max = np.zeros(3)
max[0] = Runge(first[2], second[1])
max[1] = Runge(first[4], second[2])
max[2] = Runge(first[6], second[3])

print('pi/2 + 0.4:', max[0])
print('pi/2 + 0.8:', max[1])
print('pi/2 + 1.2:', max[2])
print('max       :', np.amax(max))

print('-----------------------------------------')


def Precise(t):
    return np.sin(t) * (- np.cos(t))


h = 0.2
t = np.pi / 2
precise = np.zeros(7)
precise[0] = 0.0
print('precise ', 0, ':', round(precise[0], 6))
for i in range(0, 6):
    t += h
    print('precise ', i+1, ':', round(Precise(t), 6))
    precise[i+1] = round(Precise(t), 6)


print('-----------------------------------------')

print('pi/2      :', Runge(first[0], precise[0]))
print('pi/2 + 0.2:', Runge(first[1], precise[1]))
print('pi/2 + 0.4:', Runge(first[2], precise[2]))
print('pi/2 + 0.6:', Runge(first[3], precise[3]))
print('pi/2 + 0.8:', Runge(first[4], precise[4]))
print('pi/2 + 1.0:', Runge(first[5], precise[5]))
print('pi/2 + 1.2:', Runge(first[6], precise[6]))

print('-----------------------------------------')

def EulerModified(y, t, h, f, plus):
    y_half = y + h/2 * f(y, t)
    return y + h * f(y_half, t + plus),  y_half

h = 0.2
t = np.pi / 2
prev = 0.0

first_modified = np.zeros(7)
first_modified[0] = 0.0


for i in range(0, 6):
    prev, half = EulerModified(prev, t, h, f, 0.1)
    print(i+1, '1/2 :', round(half, 6))
    print(i+1, '    :', round(prev, 3))
    print()
    t += h
    first_modified[i + 1] = round(prev, 6)

print('-----------------------------------------')

h = 0.4
t = np.pi / 2
prev = 0.0

second_modified = np.zeros(4)
second_modified[0] = 0.0

for i in range(0, 3):
    prev, half = EulerModified(prev, t, h, f, 0.2)
    print(i + 1, '1/2 :', round(half, 6))
    print(i + 1, '    :', round(prev, 6))
    print()
    t += h
    second_modified[i + 1] = round(prev, 6)

print('-----------------------------------------')

max_modified = np.zeros(3)
max_modified[0] = Runge(first_modified[2], second_modified[1])
max_modified[1] = Runge(first_modified[4], second_modified[2])
max_modified[2] = Runge(first_modified[6], second_modified[3])

print('pi/2 + 0.4:', max_modified[0])
print('pi/2 + 0.8:', max_modified[1])
print('pi/2 + 1.2:', max_modified[2])
print('max       :', np.amax(max_modified))

print('-----------------------------------------')

print('pi/2      :', Runge(first_modified[0], precise[0]))
print('pi/2 + 0.2:', Runge(first_modified[1], precise[1]))
print('pi/2 + 0.4:', Runge(first_modified[2], precise[2]))
print('pi/2 + 0.6:', Runge(first_modified[3], precise[3]))
print('pi/2 + 0.8:', Runge(first_modified[4], precise[4]))
print('pi/2 + 1.0:', Runge(first_modified[5], precise[5]))
print('pi/2 + 1.2:', Runge(first_modified[6], precise[6]))

import matplotlib.pyplot as plt

x1 = np.zeros(7)
t = np.pi / 2
for i in range(0, 7):
    x1[i] = t
    t += 0.2

x = np.linspace(np.pi/2, np.pi/2 + 1.2, 100, endpoint=True)
plt.plot(x, Precise(x), ls='--',label="Precise", color = 'cyan')
plt.plot(x1,first, ls='--', label = "Euler", color = 'magenta')
plt.plot(x1,first_modified, ls='--', label = "Modified Euler", color = 'black')
plt.legend()
plt.grid('True')
plt.savefig("pic_1.png", dpi = 500)
plt.show()