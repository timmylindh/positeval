import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FormatStrFormatter

plt.ylabel('Average Relative error')
plt.xlabel("Range")

filesFloat = ["../../matrices/error/32/R0.0001S10", "../../matrices/error/32/R0.001S10", "../../matrices/error/32/R0.01S10", "../../matrices/error/32/R0.1S10", 
"../../matrices/error/32/R1S10", "../../matrices/error/32/R10S10", "../../matrices/error/32/R100S10", "../../matrices/error/32/R1000S10"]

filesPosit = ["../../matrices/error/posit/R0.0001S10", "../../matrices/error/posit/R0.001S10", "../../matrices/error/posit/R0.01S10", "../../matrices/error/posit/R0.1S10", 
"../../matrices/error/posit/R1S10", "../../matrices/error/posit/R10S10", 
"../../matrices/error/posit/R100S10", "../../matrices/error/posit/R1000S10"]

x = [0.0001 ,0.001, 0.01, 0.1, 1, 10, 100, 1000]
xi = list(range(len(x)))
plt.xticks(xi, x)

yfloat = []
yposit = []

for file in filesFloat:
    fd = open(file)
    values = fd.readlines()
    yfloat.append(float(values[3]))

for file in filesPosit:
    fd = open(file)
    values = fd.readlines()
    yposit.append(float(values[3]))

plt.plot(yfloat, marker='o', linestyle='--', label='float')
plt.plot(yposit, marker='o', linestyle='--', label='posit')

plt.legend()
plt.title("Float32 and Posit32 comparison")


# shobidobi 
# ett diagram för varje matrix size (10, 100, 1000, kanske 10000)
# ett diagram för varje error (average, mean, min, max)
# en linje för p32 och en för f32
# 
#
#
#

# plt.plot([6,8,10,18])

plt.show()


