from Simplex import Simplex
objective = ('minimize', '1x_1 + 2x_2')
constraints = ['4x_1 - 2x_2 <= 12', '-1x_1 + 3x_2 <= 6', '2x_1 + 4x_2 >= 16']
Lp_system = Simplex(num_vars=2, constraints=constraints, objective_function=objective)

print(Lp_system.solution)
# {'x_2': Fraction(6, 5), 'x_1': Fraction(3, 5)}
print("Function Solution: {0} {1}".format(Lp_system.optimize_val, objective[0]))
# 17/5