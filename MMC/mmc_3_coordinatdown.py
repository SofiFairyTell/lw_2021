import matplotlib as matplotlib
import numpy as np
from numpy import pi, cos, sin, abs, sqrt, exp
import matplotlib.pyplot as plt
from scipy import optimize


def foo(x, y):
	# return (x-1)**2+(y-1)**2-x*y
	return x*x*x+y*y-3*x-2*y+2


phi = 0.5 * (1.0 + sqrt(5.0))


# Поиск минимума функции одной переменной методом золотого сечения
# f - входная функция двух аргументов, eps - абсолютная погрешность
# X логическое значение: false минимизировать по первому аргументы, true по второму,
# par - значение зафиксированной переменной.

def minimize(foo, eps, a, b, X_fix, par):
	dd = abs(foo(b, par) - foo(a, par))
	if X_fix:
		dd = abs(foo(par, b) - foo(par, a))
	if dd < eps:
		return (a + b) / 2
	else:
		t = (b - a) / phi
		x1, x2 = b - t, a + t
		q = foo(x1, par)
		Q = foo(x2, par)
		if X_fix:
			q = foo(par, x1)
			Q = foo(par, x2)
		if q >= Q:
			return minimize(foo, eps, x1, b, X_fix, par)
		else:
			return minimize(foo, eps, a, x2, X_fix, par)


xmin, xmax = 0, 2
ymin, ymax = 0, 2
x0, y0 = 0.5, 0.5
eps = 0.001

X = np.arange(xmin, xmax, 0.010)
Y = np.arange(ymin, ymax, 0.010)
X, Y = np.meshgrid(X, Y)

plt.contour(X, Y, foo(X, Y), 50)
plt.plot(x0, y0, 'bo')

i = xo = yo = 0
while abs(foo(xo, yo) - foo(x0, y0)) > eps:
	i += 1
	if i > 10**3:
		print('break!')
		break
	xo, yo = x0, y0
	x0 = minimize(foo, eps, xmin, xmax, False, y0)
	y0 = minimize(foo, eps, ymin, ymax, True, x0)
	plt.plot([xo, xo, x0], [yo, y0, y0], '-b')

plt.plot(x0, y0, 'ro')
print('Итераций: ', i)
print(x0, y0)
plt.show()
