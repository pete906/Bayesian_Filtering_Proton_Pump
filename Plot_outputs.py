import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("Output.csv", delimiter=",", names=["Signal", "Observed", "MAPestimate"])

time=  list(range(1, len(data['Signal'])+1))

plt.plot(time,data['Observed'])
plt.plot(time,data['MAPestimate'])
plt.plot(time,data['Signal'])
plt.legend(['Observed data', 'Unobservable Signal','MAP estimate for Signal'])
plt.xlabel('Time (s)')
plt.ylabel('Observed data')
plt.show()
