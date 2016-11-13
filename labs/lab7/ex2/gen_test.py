import numpy as np

def f(n, arr):
    result = 0
    for num in arr:
        result += abs(n-num)
    return result

array = sorted(np.random.randint(1,1000, size=200))
f_vals = np.zeros(200)
minimum = f(array[0], array)
minimum_n = array[0]

idx = 0
for n in array:
    result = f(n, array) 
    f_vals[idx] = result
    if result < minimum:
        minimum = result
        minimum_n = n
    idx += 1

print "minimum: ", minimum, "n: ", minimum_n
print 200
for i in range(200):
    print array[i], " ", f_vals[i]

