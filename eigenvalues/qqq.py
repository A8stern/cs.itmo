import numpy as np
import random

k = 10
n = random.randint(1, k)

A = np.array([[4, 1, -2, 2],
              [1, 2, 0, 1],
              [-2, 0, 3, -2],
              [2, 1, -2, -1]])

B = np.array([[0, 1.0],
              [-1.0, 0]])

C = np.random.randint(1, k, (n, n))
print(C)

file_path_in = 'in.txt'

with open(file_path_in, 'w') as file:
    file.writelines(str(n) + "\n")
    for i in range(n):
        for j in range(n):
            file.writelines(str(C[i][j]) + " ")
        file.writelines("\n")


eigenvalues, eigenvectors = np.linalg.eig(C)

formatted_eigenvalues = ["{:.6g}".format(val) for val in eigenvalues]
print(formatted_eigenvalues)

file_path_out = 'out.txt'

with open(file_path_out, 'w') as file:
    for i in range(n):
        file.writelines(formatted_eigenvalues[i] + "\n")