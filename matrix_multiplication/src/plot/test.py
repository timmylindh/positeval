import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FormatStrFormatter
import matplotlib.ticker as ticker

plt.ylabel('Relative error')
plt.xlabel("Range")

filesFloat = ["../../matrices/error/32/R0.0001S256", "../../matrices/error/32/R0.001S256", "../../matrices/error/32/R0.01S256", "../../matrices/error/32/R0.1S256", 
"../../matrices/error/32/R1S256", "../../matrices/error/32/R10S256", "../../matrices/error/32/R100S256", "../../matrices/error/32/R1000S256", "../../matrices/error/32/R10000S256"]

filesPosit = ["../../matrices/error/posit/R0.0001S256", "../../matrices/error/posit/R0.001S256", "../../matrices/error/posit/R0.01S256", "../../matrices/error/posit/R0.1S256", 
"../../matrices/error/posit/R1S256", "../../matrices/error/posit/R10S256", 
"../../matrices/error/posit/R100S256", "../../matrices/error/posit/R1000S256", "../../matrices/error/posit/R10000S256"]

x = [0.0001 ,0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000]
xi = list(range(len(x)))
plt.xticks(xi, x)

yfloatMin = []
ypositMin = []
yfloatMax = []
ypositMax = []
yfloatAvg = []
ypositAvg = []

for file in filesFloat:
    fd = open(file)
    values = fd.readlines()
    yfloatMin.append(float(values[0]))

for file in filesPosit:
    fd = open(file)
    values = fd.readlines()
    ypositMin.append(float(values[0]))

for file in filesFloat:
    fd = open(file)
    values = fd.readlines()
    yfloatMax.append(float(values[1]))

for file in filesPosit:
    fd = open(file)
    values = fd.readlines()
    ypositMax.append(float(values[1]))

for file in filesFloat:
    fd = open(file)
    values = fd.readlines()
    yfloatAvg.append(float(values[3]))

for file in filesPosit:
    fd = open(file)
    values = fd.readlines()
    ypositAvg.append(float(values[3]))


plt.plot(ypositMin, marker='o',  label='Posit Min')
plt.plot(ypositMax, marker='v',  label='Posit Max')
plt.plot(ypositAvg, marker='x',  label='Posit Average')
plt.plot(yfloatMin, marker='D', markerfacecolor='none', markeredgecolor = 'black', linestyle='--', label='IEEE 754 Min')
plt.plot(yfloatMax, marker='^', markerfacecolor='none', markeredgecolor = 'black', linestyle='--', label='IEEE 754 Max')
plt.plot(yfloatAvg, marker='+', markerfacecolor='none', markeredgecolor = 'black', linestyle='--', label='IEEE 754 Average')

ax = plt.gca()
ax.yaxis.set_major_locator(ticker.MultipleLocator(0.00000002))

plt.ylim([0, 3e-7])

plt.legend()
plt.title("256x256 Matrix")

plt.show()


